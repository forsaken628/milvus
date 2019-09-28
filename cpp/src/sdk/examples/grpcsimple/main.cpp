// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include <getopt.h>
#include <libgen.h>
#include <cstring>
#include <string>

#include "src/ClientTest.h"

void
print_help(const std::string& app_name);

int
main(int argc, char* argv[]) {
    printf("Client start...\n");

    std::string app_name = basename(argv[0]);
    static struct option long_options[] = {{"server", optional_argument, 0, 's'},
                                           {"port", optional_argument, 0, 'p'},
                                           {"help", no_argument, 0, 'h'},
                                           {NULL, 0, 0, 0}};

    int option_index = 0;
    std::string address = "127.0.0.1", port = "19530";
    app_name = argv[0];

    int value;
    while ((value = getopt_long(argc, argv, "s:p:h", long_options, &option_index)) != -1) {
        switch (value) {
            case 's': {
                char* address_ptr = strdup(optarg);
                address = address_ptr;
                free(address_ptr);
                break;
            }
            case 'p': {
                char* port_ptr = strdup(optarg);
                port = port_ptr;
                free(port_ptr);
                break;
            }
            case 'h':
            default:
                print_help(app_name);
                return EXIT_SUCCESS;
        }
    }

    ClientTest test;
    test.Test(address, port);

    printf("Client stop...\n");
    return 0;
}

void
print_help(const std::string& app_name) {
    printf("\n Usage: %s [OPTIONS]\n\n", app_name.c_str());
    printf("  Options:\n");
    printf("   -s --server   Server address, default 127.0.0.1\n");
    printf("   -p --port     Server port, default 19530\n");
    printf("   -h --help     Print help information\n");
    printf("\n");
}
