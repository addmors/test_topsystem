клонирование через терминал:
	git clone --recursive https://github.com/addmors/test_topsystem

генерация через Cmake:
	cmake -G "Visual Studio 17 2022" -A x64 -S . -B build

если есть vscode:
	скачиваем "C/C++ Extension Pack"
	или по отдельности C/C++, C/C++ Themes, CMake Tools
	перезаходим в корень (перезапуская vscode)
	генерируем зайдя в корневой CMakeLists.txt + "ctrl+s"
	дальше как в студии f5 => сборка + запуск 
	"launch.json" уже настроен.
	
