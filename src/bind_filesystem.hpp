#pragma once

#include <memory>
#include <iostream>
#include <fstream>

#include <duktape-cpp/DuktapeCpp.h>

#define CUTE_FILES_IMPLEMENTATION
#include <cute_files.h>

#define CUTE_PATH_IMPLEMENTATION
#include <cute_path.h>

#if defined(_WIN32)
#include <windows.h>
#endif
#if defined(__linux__)
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

namespace FileSystemBinder {

    class Directory {
    public:
        explicit Directory() {}

        /**
         * @brief collect files recursively
         * @private
         * @param vv
         * @param dir
         * @param ext
         * @param recursive
         * @param filenameOnly
         */
        void RecursiveCollect(std::vector<std::string> *vv, std::string dir, std::string *ext, bool recursive,
                              bool filenameOnly) {
            cf_dir_t _dir;
            cf_dir_open(&_dir, dir.c_str());
            while (_dir.has_next) {
                cf_file_t _file;
                cf_read_file(&_dir, &_file);

                if ((strcmp(_file.name, ".") == 0) || (strcmp(_file.name, "..") == 0)) {
                    // TODO: Do we need to do something in this case ???
                } else {
                    if ((_file.is_dir) && (recursive)) {
                        RecursiveCollect(vv, _file.path, ext, recursive, filenameOnly);
                    }
                    if ((ext == NULL) || (strcmp(ext->c_str(), _file.ext) == 0)) {
                        if (filenameOnly) {
                            vv->push_back(std::string(_file.name));
                        } else {
                            vv->push_back(std::string(_file.path));
                        }
                    }
                }

                cf_dir_next(&_dir);
            }
            cf_dir_close(&_dir);
        }

        std::string GetCurrentDir() {
#if defined(_WIN32)
            char NPath[MAX_PATH];
            GetCurrentDirectory(MAX_PATH, NPath);
            return std::string(NPath);
#endif
#if defined(__linux__)
            return std::string(get_current_dir_name());
#endif
            // TODO: need implementation for other platforms

            return 0;
        }

        int SetCurrentDir(std::string dir) {
#if defined(_WIN32)
            return SetCurrentDirectory(dir.c_str());
#endif
#if defined(__linux__)
            return chdir(dir.c_str());
#endif
            // TODO: need implementation for other platforms

            return -1;
        }

        int MakeDir(std::string dir) {
#if defined(_WIN32)
            return CreateDirectoryA(dir.c_str(), 0);
#endif
#if defined(__linux__)
            return mkdir(dir.c_str(), 0);
#endif
            // TODO: need implementation for other platforms

            return -1;
        }

        int RemoveDir(std::string dir) {
#if defined(_WIN32)
            return RemoveDirectoryA(dir.c_str());
#endif
#if defined(__linux__)
            return rmdir(dir.c_str());
#endif
            // TODO: need implementation for other platforms

            return -1;
        }

        int RemoveFile(std::string filename)
        {
            return remove(filename.c_str());
        }

        std::vector<std::string> CollectAllFiles(std::string dir, bool recursive, bool filenameOnly) {
            std::vector<std::string> files;
            RecursiveCollect(&files, dir, NULL, recursive, filenameOnly);
            return files;
        }

        std::vector<std::string>
        CollectFilesWithExt(std::string dir, std::string ext, bool recursive, bool filenameOnly) {
            std::vector<std::string> files;
            RecursiveCollect(&files, dir, &ext, recursive, filenameOnly);
            return files;
        };

        std::vector<std::string>
        CollectFilesContainingString(std::string dir, std::string str, std::string ext, bool recursive,
                                     bool filenameOnly) {
            std::vector<std::string> files;
            std::vector<std::string> filtered;

            if (ext.compare("") == 0) {
                RecursiveCollect(&files, dir, NULL, recursive, filenameOnly);
            } else {
                RecursiveCollect(&files, dir, &ext, recursive, filenameOnly);
            }

            for (int i = 0; i < files.size(); i++) {
                if (files[i].find(str) != std::string::npos) {
                    filtered.push_back(files[i]);
                }
            }

            return filtered;
        };

        std::string ReadTextFile(std::string filename)
        {
            std::ifstream inFile;
            inFile.open(filename);

            if (!inFile) {
                std::cout << "Unable to open file " << filename << std::endl;
                return 0;
            }

            std::string content((std::istreambuf_iterator<char>(inFile)),
                    (std::istreambuf_iterator<char>()));

            inFile.close();

            return content;
        }

        std::vector<std::string> ReadLineByLine(std::string filename)
        {
            std::vector<std::string> lines;
            std::ifstream inFile;
            inFile.open(filename);

            if (!inFile) {
                std::cout << "Unable to open file " << filename << std::endl;
                return lines;   // empty vector
            }

            std::string str;
            while (std::getline(inFile, str))
            {
                lines.push_back(str);
            }

            inFile.close();

            return lines;
        }

        int WriteTextFile(std::string filename, std::string content)
        {
            std::ofstream ouFile;
            ouFile.open(filename);

            if (!ouFile) {
                std::cout << "Unable to open file " << filename << std::endl;
                return -1;
            }

            ouFile << content;

            ouFile.close();

            return 0;
        }

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template<class Inspector>
        static void inspect(Inspector &i) {
            i.construct(&std::make_shared<Directory>);
            i.method("collectAllFiles", &Directory::CollectAllFiles);
            i.method("collectFilesWithExt", &Directory::CollectFilesWithExt);
            i.method("collectFilesContainingString", &Directory::CollectFilesContainingString);
            i.method("getCurrent", &Directory::GetCurrentDir);
            i.method("setCurrent", &Directory::SetCurrentDir);
            i.method("make", &Directory::MakeDir);
            i.method("remove", &Directory::RemoveDir);
            i.method("readTextFile",&Directory::ReadTextFile);
            i.method("readLineByLine",&Directory::ReadLineByLine);
            i.method("writeTextFile",&Directory::WriteTextFile);
            i.method("removeFile",&Directory::RemoveFile);
        }
    };

    class Path {
    public:
        explicit Path() {}

        std::string GetFilename(std::string path) {
            char out[CUTE_PATH_MAX_PATH];
            char pop[CUTE_PATH_MAX_PATH];

            path_pop(path.c_str(), out, pop);

            return std::string(pop);
        }

        std::string GetDirectory(std::string path) {
            char out[CUTE_PATH_MAX_PATH];
            char pop[CUTE_PATH_MAX_PATH];

            path_pop(path.c_str(), out, pop);

            return std::string(out);
        }

        std::string GetExtension(std::string path) {
            char out[CUTE_PATH_MAX_PATH];
            char ext[CUTE_PATH_MAX_PATH];

            path_pop_ext(path.c_str(), out, ext);

            return std::string(ext);
        }

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template<class Inspector>
        static void inspect(Inspector &i) {
            i.construct(&std::make_shared<Path>);
            i.method("getFilename", &Path::GetFilename);
            i.method("getDirectory", &Path::GetDirectory);
            i.method("getExtension", &Path::GetExtension);
        }
    };

}
