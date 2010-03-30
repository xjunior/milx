#include <iostream>
#include <milx/application.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "daemon.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

std::string host = "0.0.0.0";
int port = 8888;
fs::path _path = fs::current_path(), _pub, _tmp, _mods;
int pid = getpid();

#define PIDFILE _tmp / "milx-server.pid"

inline void validate_existence(fs::path& path)
{
	if (!fs::exists(path)) {
		std::cerr << path << " does not exist." << std::endl;
		exit(1);
	}
}

bool parse_options(int argc, char *argv[])
{
	po::options_description opts("milx-server usage");
	po::variables_map vm;
	opts.add_options()
		("help", "show this help")
		("port,p", po::value<int>(), "set the server port [default to 8080]")
		("host,h", po::value<std::string>(), "the host to serve [default to 0.0.0.0]")
		("path", po::value<fs::path>(), "path to the project [default to current working dir]")
		("public", po::value<fs::path>(), "path to the public directory [default is to <path>/public]")
		("modules", po::value<fs::path>(), "path to the modules directory [default is to <path>/modules]")
		("tmp", po::value<fs::path>(), "path to the tmp directory [default is to <path>/tmp]")
		("plugins", po::value<fs::path>(), "path to the plugins directory [default is <path>/plugins")
	;
	po::store(po::parse_command_line(argc, argv, opts), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << opts << std::endl;
		return false;
	}

	// Server stuff
	if (vm.count("host")) host = vm["host"].as<std::string>();
	if (vm.count("port")) port = vm["port"].as<int>();

	// Paths
	if (vm.count("path")) _path =  vm["path"].as<fs::path>();
	validate_existence(_pub  = vm.count("public") ? vm["public"].as<fs::path>() : _path / "public");
	validate_existence(_tmp  = vm.count("tmp") ? vm["tmp"].as<fs::path>() : _path / "tmp");
	validate_existence(_mods = vm.count("modules") ? vm["modules"].as<fs::path>() : _path / "modules");
}

inline void create_pid_file()
{
	fs::ofstream fstr(PIDFILE);
	fstr << pid;
	fstr.close();
}

inline void remove_pid_file()
{
	fs::remove(PIDFILE);
}

inline void load_app_extensions(Milx::Application& app, const fs::path& path)
{
	fs::directory_iterator end_iter;

	for (fs::directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr) {
		try {
			if (fs::is_regular_file(dir_itr->status()) &&
				dir_itr->path().extension().compare(".so") == 0)
				app.loadModule(dir_itr->path());
			else if (fs::is_directory(*dir_itr))
				load_app_extensions(app, dir_itr->path());
		} catch (const std::exception & ex) { }
	}
}

int main(int argc, char *argv[])
{
	if (parse_options(argc, argv)) {
		Milx::Application app;
		load_app_extensions(app, _path);

		Milx::Server::Daemon daemon(app, port);

		daemon.start();
		create_pid_file();
		std::cin.get(); // it must be changed :D
		remove_pid_file();
		daemon.stop();
	}

	return 0;
}

