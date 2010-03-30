#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "daemon.hpp"
#include "../application.hpp"
#include "../project_loader.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

std::string host = "0.0.0.0";
int port = 8888;
fs::path _path = fs::current_path(), _pub, _tmp, _mods;
int pid = getpid();

#define PIDFILE _tmp / "milx-server.pid"

bool parse_options(int argc, char *argv[])
{
	po::options_description opts("milx-server usage");
	po::variables_map vm;
	opts.add_options()
		("help", "show this help")
		("port,p", po::value<int>(), "set the server port [default to 8080]")
		("host,h", po::value<std::string>(), "the host to serve [default to 0.0.0.0]")
		("path", po::value<fs::path>(), "path to the project [default to current working dir]")
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

int main(int argc, char *argv[])
{
	if (parse_options(argc, argv)) {
		Milx::Application app;
		Milx::ProjectLoader::load(app, _path);
		Milx::Server::Daemon daemon(app, port);

		daemon.start();
		create_pid_file();
		std::cin.get(); // it must be changed :D
		remove_pid_file();
		daemon.stop();
	}

	return 0;
}

