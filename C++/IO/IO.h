#ifndef IO_HELPER_H
#define IO_HELPER_H

#include<iostream>
#include<fstream>
#include<string>
#include"../Structures/Graph.h"

class IO {
    public:
        IO(std::string path);
        std::vector<Graph> read(const std::string& filename);
        std::string get_path();
        // void run_test(const std::vector<Graph>& )
    private: 
        std::string path;
};

#endif//IO_HELPER_H