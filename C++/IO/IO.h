#ifndef IO_HELPER_H
#define IO_HELPER_H

#include"../Structures/Graph.h"
#include"Time.h"
#include"../Algorithms/Algorithms.h"

#include<iostream>
#include<fstream>
#include<string>


class IO {    
    public:
        struct TSPName {
            std::string name;
            TSP algorithm;
        };

        IO(std::string path);
        std::vector<Graph> read(const std::string& filename);
        std::string get_path();
        void test_output(const std::string& output_filename, const std::vector<Graph>& GS, const std::vector<TSPName>& fs);

    private: 
        std::string path;
};

#endif//IO_HELPER_H