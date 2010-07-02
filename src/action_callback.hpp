#ifndef MILX_ACTION_CALLBACK_HPP
#define MILX_ACTION_CALLBACK_HPP

#define MILX_CALLBACK_FUNCTION(a) void (T::*a)(Milx::WebCall&)

namespace Milx
{
	class WebCall;
	namespace ActionCallback
	{
		class CallbackBase
		{
		public:
			virtual void call(Milx::WebCall&)=0;
		};

		template <class T> class Callback : public CallbackBase
		{
		public:
			Callback(T* obj, MILX_CALLBACK_FUNCTION(func))
				:	_obj(obj), _func(func)
			{
			}
			virtual void call(Milx::WebCall &call)
			{
				(*_obj.*_func)(call);
			}
		private:
			MILX_CALLBACK_FUNCTION(_func);
			T *_obj;
		};

		template <class T>
		Callback<T>* make_callback(T *obj, MILX_CALLBACK_FUNCTION(func))
		{
			return new Callback<T>(obj, func);
		}
	}
}

#endif
