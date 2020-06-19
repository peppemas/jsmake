#include <memory>
#include <iostream>

#include <duktape-cpp/DuktapeCpp.h>

#define CUTE_FILES_IMPLEMENTATION
#include <cute_files.h>

#define CUTE_PATH_IMPLEMENTATION
#include <cute_path.h>

#if defined(_WIN32)
#include <windows.h>
#endif

namespace FileSystem {

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
			void RecursiveCollect(std::vector<std::string> *vv, std::string dir, std::string *ext, bool recursive, bool filenameOnly) {
				cf_dir_t _dir;
				cf_dir_open(&_dir, dir.c_str());
				while (_dir.has_next)
				{
					cf_file_t _file;
					cf_read_file(&_dir, &_file);

					if (( strcmp(_file.name,".") == 0) || ( strcmp(_file.name,"..") == 0)) 
					{
						// TODO: Do we need to do something in this case ???
					} else {
						if ((_file.is_dir)&&(recursive)) {
							RecursiveCollect(vv, _file.path, ext, recursive, filenameOnly);
						}
						if ((ext == NULL) || (strcmp(ext->c_str(),_file.ext) == 0)) {
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

			std::string GetCurrentDir()
			{
                #if defined(_WIN32)
                char NPath[MAX_PATH];
                GetCurrentDirectory(MAX_PATH, NPath);
                return std::string(NPath);
                #endif

                // TODO: need implementation for other platforms

                return 0;
			}

			int SetCurrentDir(std::string dir)
            {
			    #if defined(_WIN32)
                if (!SetCurrentDirectory(dir.c_str())) return -1;
                #endif
                // TODO: need implementation for other platforms

                return 0;
            }

			int MakeDir(std::string dir)
            {
                #if defined(_WIN32)
                if (!CreateDirectoryA(dir.c_str(), 0)) return -1;
                #endif
                // TODO: need implementation for other platforms

                return 0;
            }

            int RemoveDir(std::string dir)
            {
                #if defined(_WIN32)
			    if (!RemoveDirectoryA(dir.c_str())) return -1;
                #endif
                // TODO: need implementation for other platforms

			    return 0;
            }

			std::vector<std::string> CollectAllFiles(std::string dir, bool recursive, bool filenameOnly) 
			{ 
				std::vector<std::string> files;
				RecursiveCollect(&files, dir, NULL, recursive, filenameOnly);
				return files;
			}

			std::vector<std::string> CollectFilesWithExt(std::string dir, std::string ext, bool recursive, bool filenameOnly)
			{
				std::vector<std::string> files;
				RecursiveCollect(&files, dir, &ext, recursive, filenameOnly);
				return files;
			};

			std::vector<std::string> CollectFilesContainingString(std::string dir, std::string str, std::string ext, bool recursive, bool filenameOnly)
			{
				std::vector<std::string> files;
				std::vector<std::string> filtered;

				if (ext.compare("") == 0) {
					RecursiveCollect(&files, dir, NULL, recursive, filenameOnly);
				} else {
					RecursiveCollect(&files, dir, &ext, recursive, filenameOnly);
				}

				for (int i=0; i<files.size(); i++) {
					if (files[i].find(str) != std::string::npos) {
						filtered.push_back(files[i]);
					}
				}

				return filtered;
			};

		    /**
		     * Inspect method defines class meta information (methods, properties etc..)
		     * You can define `inspect` method inline or specialize `duk::Inspect` for your class
		     */
		    template <class Inspector>
		    static void inspect(Inspector &i) 
		    {
		        i.construct(&std::make_shared<Directory>);
		        i.method("collectAllFiles", &Directory::CollectAllFiles);
		        i.method("collectFilesWithExt", &Directory::CollectFilesWithExt);
		        i.method("collectFilesContainingString", &Directory::CollectFilesContainingString);
                i.method("getCurrent", &Directory::GetCurrentDir);
                i.method("setCurrent", &Directory::SetCurrentDir);
                i.method("make", &Directory::MakeDir);
                i.method("remove", &Directory::RemoveDir);
		    }
	};

	class Path {
		public:
			explicit Path() {}

			std::string GetFilename(std::string path) 
			{
				char out[CUTE_PATH_MAX_PATH];
                char pop[CUTE_PATH_MAX_PATH];

                path_pop(path.c_str(), out, pop);

                return std::string(pop);
			}

			std::string GetDirectory(std::string path)
			{
				char out[CUTE_PATH_MAX_PATH];
                char pop[CUTE_PATH_MAX_PATH];

                path_pop(path.c_str(), out, pop);

                return std::string(out);
			}

			std::string GetExtension(std::string path)
			{
				char out[CUTE_PATH_MAX_PATH];
                char ext[CUTE_PATH_MAX_PATH];

                path_pop_ext(path.c_str(), out, ext);

                return std::string(ext);
			}

		    /**
		     * Inspect method defines class meta information (methods, properties etc..)
		     * You can define `inspect` method inline or specialize `duk::Inspect` for your class
		     */
		    template <class Inspector>
		    static void inspect(Inspector &i) 
		    {
		        i.construct(&std::make_shared<Path>);
		        i.method("getFilename", &Path::GetFilename);
		        i.method("getDirectory", &Path::GetDirectory);
		        i.method("getExtension", &Path::GetExtension);
		    }
	};

}

