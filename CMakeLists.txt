cmake_minimum_required(VERSION 3.8)
project(graph_project_3_grafos_1_camino)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        .idea/codeStyles/Project.xml
        .idea/.name
        .idea/graph-project-3_grafos_1_camino.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        .vscode/settings.json
        .vscode/tasks.json
        Graph/edge.h
        Graph/graph.h
        Graph/node.h
        test/main.cpp
        ui/fonts/arial.ttf
        ui/include/Views/BFS.hpp
        ui/include/Views/Bipartite.hpp
        ui/include/Views/DFS.hpp
        ui/include/Views/Kruskal.hpp
        ui/include/Views/Prim.hpp
        ui/include/Views/Properties.hpp
        ui/include/Views/SCC.hpp
        ui/include/Views/View.hpp
        ui/include/config.hpp
        ui/include/Console.hpp
        ui/include/GraphUI.hpp
        ui/include/GraphView.hpp
        ui/include/Grid.hpp
        ui/include/LoadGraph.hpp
        ui/include/Menu.hpp
        ui/include/UI.hpp
        ui/input/graph-01.txt
        ui/input/graph-02.txt
        ui/input/graph-03.txt
        ui/input/graph-04.txt
        ui/input/graph-05.txt
        ui/input/graph-06.txt
        ui/input/graph-07.txt
        ui/input/graph-08.txt
        ui/input/graph-09.txt
        ui/sound/music.wav
        ui/src/Console.cpp
        ui/src/GraphUI.cpp
        ui/src/Grid.cpp
        ui/src/LoadGraph.cpp
        ui/src/main.cpp
        ui/src/Menu.cpp
        ui/src/UI.cpp
        ui/README.md
        .gitignore
        contribution.md
        LICENSE
        Makefile
        README.md
        window)

add_executable(graph_project_3_grafos_1_camino ${SOURCE_FILES})