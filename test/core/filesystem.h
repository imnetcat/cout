#pragma once
#include "../../src/core/config.h"
#ifdef INDEBUG
#include "../../src/core/testing/module_test.h"
#include "../../src/core/testing/assert.h"
#include "../../src/core/filesystem/file.h"
#include "../../src/core/filesystem/dir.h"
#include "../../src/core/filesystem/context_menu.h"
#include "../../src/core/filesystem/explorer.h"
using namespace Cout;
using namespace Cout::Core::Testing;
using namespace Cout::Core::Filesystem;
using namespace Cout::Exceptions::Core;

const Path testing_files_root = "./test/files";

ModuleTest FilesystemUnitTests = {
	{
		new UnitTest([]() {
			const auto p = testing_files_root / "1.png";
			FileDescryptor f(p);
			ASSERT_EQUAL(f.path(), p);
		}),
		new UnitTest([]() {
			const auto dir = testing_files_root;
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, FileDescryptor file(dir));
		}),
		new UnitTest([]() {
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, FileDescryptor file(""));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, file.path(testing_files_root));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, file.path(""));
		}),
		new UnitTest([]() {
			const auto unexisted_file = "akldjgoieuriaikojdbafhb.txt";
			FileDescryptor file(unexisted_file);
			ASSERT_BOOL(!file.exist());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			ASSERT_BOOL(file.exist());
		}),
		new UnitTest([]() {
			const auto unexisted_file = "akldjgoieuriaikojdbafhb.txt";
			FileDescryptor file(unexisted_file);
			ASSERT_EQUAL(file.path(), unexisted_file);
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			ASSERT_EQUAL(file.path(), name);
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "bar/1.jpg";
			FileDescryptor file(name);
			ASSERT_EQUAL(file.size(), fs::file_size(name));
		}),
		new UnitTest([]() {
			const auto unexisted_file = "akldjgoieuriaikojdbafhb.txt";
			FileDescryptor file(unexisted_file);
			ASSERT_EXCEPTION(file_not_exist, file.size());
		}),
		new UnitTest([]() {
			const auto unexisted_file = "akldjgoieuriaikojdbafhb.txt";
			FileDescryptor file(unexisted_file);
			ASSERT_EXCEPTION(file_not_exist, file.remove());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "new_file.txt";
			std::ofstream new_file(testing_files_root / "new_file.txt", std::ios::binary);
			new_file.close();
			FileDescryptor file(name);
			file.remove();
			ASSERT_BOOL(!file.exist());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "bar/1.jpg";
			FileDescryptor file(name);
			ASSERT_EXCEPTION(file_already_exist, file.create());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "new_file.txt";
			FileDescryptor file(name);
			file.create();
			bool result = file.exist();
			file.remove();
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "some_file.txt";
			FileDescryptor file(name);
			file.path(testing_files_root / "some_file.qwerty");
			ASSERT_EQUAL(file.path(), testing_files_root / "some_file.qwerty");
		}),

		new UnitTest([]() {
			auto name = testing_files_root / "simple text.txt";
			ReadableFile simpleText(name);
			simpleText.open();
			Binary file = simpleText.read(4, 7);
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			ASSERT_EQUAL(result, "text");
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "simple text.txt";
			File simpleText(name);
			simpleText.open4read();
			Binary file = simpleText.read(4, 7);
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			ASSERT_EQUAL(result, "text");
		}),

		new UnitTest([]() {
			Explorer explorer;
			ASSERT_EQUAL(explorer.path(), fs::current_path());
		}),
		new UnitTest([]() {
			const auto p = testing_files_root;
			DirDescryptor dir(p);
			ASSERT_EQUAL(dir.path(), p);
		}),
		new UnitTest([]() {
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, DirDescryptor dir(testing_files_root / "bar/1.jpg"));
		}),
		new UnitTest([]() {
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, DirDescryptor dir(""));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, dir.path(testing_files_root / "bar/1.jpg"));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, dir.path(""));
		}),
		new UnitTest([]() {
			const auto unexisted_directory = "akldjgoieuriaikojdbafhb";
			DirDescryptor dir(unexisted_directory);
			ASSERT_BOOL(!dir.exist());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ASSERT_BOOL(dir.exist());
		}),
		new UnitTest([]() {
			const auto unexisted_directory = "akldjgoieuriaikojdbafhb";
			DirDescryptor dir(unexisted_directory);
			ASSERT_EQUAL(dir.path(), unexisted_directory);
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ASSERT_EQUAL(dir.path(), name);
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			size_t result = 0;
			for (const auto & entry : std::filesystem::directory_iterator(name))
			{
				if (entry.is_directory())
					result += DirDescryptor(entry.path()).size();
				else
					result += FileDescryptor(entry.path()).size();
			}
			DirDescryptor dir(name);
			ASSERT_EQUAL(dir.size(), result);
		}),
		new UnitTest([]() {
			const auto unexisted_directory = "akldjgoieuriaikojdbafhb";
			DirDescryptor dir(unexisted_directory);
			ASSERT_EXCEPTION(Exceptions::Core::dir_not_exist, dir.size());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ASSERT_EXCEPTION(Exceptions::Core::dir_already_exist, dir.create());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "some_directory";
			DirDescryptor dir(name);
			dir.create();
			bool result = dir.exist();
			dir.remove();
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			const auto unexisted_directory = "akldjgoieuriaikojdbafhb";
			DirDescryptor dir(unexisted_directory);
			ASSERT_EXCEPTION(Exceptions::Core::dir_not_exist, dir.remove());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "new_dir";
			DirDescryptor new_dir(name);
			new_dir.create();
			DirDescryptor dir(name);
			dir.remove();
			ASSERT_BOOL(!dir.exist());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "some_dir";
			DirDescryptor dir(name);
			dir.path(testing_files_root);
			ASSERT_EQUAL(dir.path(), testing_files_root);
		}),

		new UnitTest([]() {
			const auto name = testing_files_root / "some_file.qwerty";
			FileDescryptor file(name);
			ContextMenu::create(file);
			bool result = file.exist();
			ContextMenu::remove(file);
			result = result && !file.exist();
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "new_dir";
			DirDescryptor dir(name);
			ContextMenu::create(dir);
			bool result = dir.exist();
			ContextMenu::remove(dir);
			result = result && !dir.exist();
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "un/existed/dir";
			DirDescryptor dir(name);
			ASSERT_BOOL(!ContextMenu::exist(dir));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ASSERT_BOOL(ContextMenu::exist(dir));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "some_unexisting file.hpy";
			FileDescryptor file(name);
			ASSERT_BOOL(!ContextMenu::exist(file));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			ASSERT_BOOL(ContextMenu::exist(file));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ASSERT_EQUAL(ContextMenu::size(dir), dir.size());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "bar/1.jpg";
			FileDescryptor file(name);
			ASSERT_EQUAL(ContextMenu::size(file), file.size());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "unexisted---dir";
			DirDescryptor dir(name);
			ASSERT_EXCEPTION(dir_not_exist, ContextMenu::size(dir));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "bar/1.jpg";
			FileDescryptor file(name);
			ASSERT_EXCEPTION(file_already_exist, ContextMenu::create(file));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ASSERT_EXCEPTION(dir_already_exist, ContextMenu::create(dir));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "non-existing-file";
			FileDescryptor file(name);
			ASSERT_EXCEPTION(file_not_exist, ContextMenu::remove(file));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "non-existing-file";
			DirDescryptor dir(name);
			ASSERT_EXCEPTION(dir_not_exist, ContextMenu::remove(dir));
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "new_dir";
			DirDescryptor dir(name);
			ContextMenu::create(dir);
			name /= "newfile.txt";
			FileDescryptor file(name);
			ContextMenu::create(file);
			ContextMenu::remove(dir);
			ASSERT_BOOL(!file.exist() && !dir.exist());
		}),
		new UnitTest([]() {
			auto name = testing_files_root;
			DirDescryptor dir(name);
			auto listing = ContextMenu::listing(dir);
			size_t count = listing.dirs.size() + listing.files.size();
			ASSERT_EQUAL(count, 10);
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "new_dir";
			DirDescryptor dir(name);
			dir.create();
			auto listing = ContextMenu::listing(dir);
			dir.remove();
			size_t count = listing.dirs.size() + listing.files.size();
			ASSERT_EQUAL(count, 0);
		}),
		new UnitTest([]() {
			auto name = testing_files_root;
			Dir dir(name);
			auto listing = ContextMenu::listing(dir);
			size_t count = listing.dirs.size() + listing.files.size();
			ASSERT_EQUAL(count, 10);
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "new_dir";
			Dir dir(name);
			dir.create();
			auto listing = ContextMenu::listing(dir);
			dir.remove();
			size_t count = listing.dirs.size() + listing.files.size();
			ASSERT_EQUAL(count, 0);
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "simple text.txt";
			File simpleText(name);
			simpleText.open4read();
			Binary file = ContextMenu::read(simpleText);
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			ASSERT_EQUAL(result, "simple text data");
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "simple text.txt";
			File simpleText(name);
			simpleText.open4read();
			Binary file;
			ContextMenu::read(simpleText, 4, [&file](const Binary&  d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			ASSERT_EQUAL(result, "simple text data");
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "simple text.txt";
			File simpleText(name);
			simpleText.open4read();
			Binary file;
			ContextMenu::read(simpleText, 100500, [&file](const Binary&  d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			ASSERT_EQUAL(result, "simple text data");
		}),
		new UnitTest([]() {
			auto fname = testing_files_root / "simple text.txt";
			auto dname = testing_files_root / "bar";
			auto root = testing_files_root;
			File file(fname);
			Dir dir(dname);
			ContextMenu::move(file, dir);
			bool result = file.exist() && file.path() == testing_files_root / "bar\\simple text.txt";
			ContextMenu::move(file, testing_files_root);
			result = result && file.exist() && file.path() == testing_files_root / "simple text.txt";
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto fname = testing_files_root / "simple text.txt";
			auto dname = testing_files_root / "bar";
			auto root = testing_files_root;
			File file(fname);
			FileDescryptor new_file(dname / "simple text.txt");
			bool result = !new_file.exist();
			Dir dir(dname);
			ContextMenu::copy(file, dir);
			result = result && file.exist() &&
				file.path() == testing_files_root / "simple text.txt" && 
				new_file.exist();
			ContextMenu::remove(new_file);
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto sname = testing_files_root / "new_dir";
			auto dname = testing_files_root / "bar";
			Dir source(sname);
			ContextMenu::create(source);
			Dir dest(dname);
			ContextMenu::move(source, dest);
			bool result = source.exist() && source.path() == testing_files_root / "bar\\new_dir";
			ContextMenu::remove(source);
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto sname = testing_files_root / "bar";
			auto dname = testing_files_root / "foo";
			auto root = testing_files_root;
			Dir source(sname);
			size_t Size = source.size();
			Dir dircopy(dname / "bar");
			bool result = !dircopy.exist();
			Dir dest(dname);
			ContextMenu::copy(source, dest);
			result = result && source.exist() &&
				source.path() == sname &&
				dircopy.exist() && Size == source.size();
			ContextMenu::remove(dircopy);
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "unexisteddir";
			Dir dir(name);
			ASSERT_EXCEPTION(dir_not_exist, ContextMenu::listing(dir));
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "foo/empty-file";
			File simpleText(name);
			ASSERT_EXCEPTION(non_readable, simpleText.open4read());
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "txt";
			File simpleText(name);
			ASSERT_EXCEPTION(file_not_exist, simpleText.open4read());
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "txt";
			File file(name);
			ASSERT_EXCEPTION(file_not_exist, ContextMenu::move(file, { "path/to/dir" }));
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "txt";
			Dir dir(name);
			ASSERT_EXCEPTION(dir_not_exist, ContextMenu::move(dir, { "path/to/dir" }));
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "foo";
			Dir dir(name);
			ASSERT_EXCEPTION(dir_not_exist, ContextMenu::move(dir, { "path/to/dir" }));
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "bar/1.jpg";
			File file(name);
			ASSERT_EXCEPTION(dir_not_exist, ContextMenu::move(file, { "path/to/dir" }));
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "bar";
			Dir dir(name);
			ASSERT_EXCEPTION(dir_already_exist, ContextMenu::move(dir, { testing_files_root }));
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "bar/1.jpg";
			File file(name);
			ASSERT_EXCEPTION(file_already_exist, ContextMenu::move(file, { testing_files_root / "bar" }));
		}),

		new UnitTest([]() {
			const auto fname = testing_files_root / "some_file.qwerty";
			Explorer explorer;
			explorer.mkfile(fname);
			bool result = File(fname).exist();
			explorer.remove(fname);
			result = result && !File(fname).exist();
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			const auto dname = testing_files_root / "new_dir";
			Explorer explorer;
			explorer.mkdir(dname);
			bool result = Dir(dname).exist();
			explorer.remove(dname);
			result = result && !Dir(dname).exist();
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "un/existed/dir";
			Explorer explorer;
			ASSERT_BOOL(!explorer.exist(name));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			Explorer explorer;
			ASSERT_BOOL(explorer.exist(name));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "some_unexisting file.hpy";
			Explorer explorer;
			ASSERT_BOOL(!explorer.exist(name));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "1.jpg";
			Explorer explorer;
			ASSERT_BOOL(explorer.exist(name));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			Explorer explorer;
			DirDescryptor dir(name);
			ASSERT_EQUAL(explorer.size(name), dir.size());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "bar/1.jpg";
			Explorer explorer;
			FileDescryptor file(name);
			ASSERT_EQUAL(explorer.size(name), file.size());
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "unexisted---dir";
			Explorer explorer;
			ASSERT_EXCEPTION(file_not_exist, explorer.size(name));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "bar/1.jpg";
			Explorer explorer;
			ASSERT_EXCEPTION(file_already_exist, explorer.mkfile(name));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root;
			Explorer explorer;
			ASSERT_EXCEPTION(dir_already_exist, explorer.mkdir(name));
		}),
		new UnitTest([]() {
			const auto name = testing_files_root / "non-existing-file";
			Explorer explorer;
			ASSERT_EXCEPTION(file_not_exist, explorer.remove(name));
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "new_dir";
			Explorer explorer;
			DirDescryptor dir(name);
			explorer.mkdir(name);
			name /= "newfile.txt";
			FileDescryptor file(name);
			explorer.mkfile(name);
			explorer.remove(dir.path());
			ASSERT_BOOL(!file.exist() && !dir.exist());
		}),
		new UnitTest([]() {
			auto name = testing_files_root;
			Explorer explorer;
			auto listing = explorer.listing(name);
			size_t count = listing.dirs.size() + listing.files.size();
			ASSERT_EQUAL(count, 10);
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "new_dir";
			DirDescryptor dir(name);
			Explorer explorer;
			explorer.mkdir(name);
			auto listing = explorer.listing(name);
			dir.remove();
			size_t count = listing.dirs.size() + listing.files.size();
			ASSERT_EQUAL(count, 0);
		}),
		new UnitTest([]() {
			auto name = testing_files_root;
			Explorer explorer;
			auto listing = explorer.listing(name);
			size_t count = listing.dirs.size() + listing.files.size();
			ASSERT_EQUAL(count, 10);
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "new_dir";
			Explorer explorer;
			Dir dir(name);
			dir.create();
			auto listing = explorer.listing(name);
			dir.remove();
			size_t count = listing.dirs.size() + listing.files.size();
			ASSERT_EQUAL(count, 0);
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "simple text.txt";
			Explorer explorer;
			Binary file = explorer.read(name);
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			ASSERT_EQUAL(result, "simple text data");
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "simple text.txt";
			Explorer explorer;
			Binary file;
			explorer.read(name, 4, [&file](const Binary& d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			ASSERT_EQUAL(result, "simple text data");
		}),
		new UnitTest([]() {
			auto name = testing_files_root / "simple text.txt";
			Explorer explorer;
			Binary file;
			explorer.read(name, 100500, [&file](const Binary& d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			ASSERT_EQUAL(result, "simple text data");
		}),
		new UnitTest([]() {
			auto fname = testing_files_root / "simple text.txt";
			auto dname = testing_files_root / "bar";
			auto root = testing_files_root;
			Explorer explorer;
			File file(fname);
			Dir dir(dname);
			bool result = file.exist();
			ASSERT_BOOL(result);
			explorer.move(testing_files_root / "simple text.txt", testing_files_root / "bar");
			result = !file.exist();
			explorer.move(testing_files_root / "bar/simple text.txt", testing_files_root);
			result = result && file.exist();
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto fname = testing_files_root / "simple text.txt";
			auto dname = testing_files_root / "bar";
			auto root = testing_files_root;
			Explorer explorer;
			FileDescryptor file(fname);
			FileDescryptor new_file(dname / "simple text.txt");
			bool result = !new_file.exist();
			explorer.copy(testing_files_root / "simple text.txt", testing_files_root / "bar");
			result = result && file.exist() && new_file.exist();
			explorer.remove(dname / "simple text.txt");
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto sname = testing_files_root / "new_dir";
			auto dname = testing_files_root / "bar";
			Explorer explorer;
			Dir source(sname);
			explorer.mkdir(testing_files_root / "new_dir");
			Dir dest(testing_files_root / "bar");
			bool result = source.exist();
			ASSERT_BOOL(result);
			explorer.move(testing_files_root / "new_dir", testing_files_root / "bar");
			result = !source.exist();
			explorer.remove(testing_files_root / "bar/new_dir");
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto sname = testing_files_root / "bar";
			auto dname = testing_files_root / "foo/bar";
			auto root = testing_files_root;
			Explorer explorer;
			Dir source(sname);
			size_t Size = source.size();
			bool result = source.exist() && Size == source.size();
			ASSERT_BOOL(result);
			explorer.move(testing_files_root / "bar", testing_files_root / "foo");
			Dir dest(dname);
			result = !source.exist() && Size == dest.size() && dest.exist();
			explorer.move(testing_files_root / "foo/bar", testing_files_root);
			result = result && source.exist() && Size == source.size();
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto sname = testing_files_root / "bar";
			auto dname = testing_files_root / "foo";
			auto root = testing_files_root;
			Explorer explorer;
			Dir source(sname);
			size_t Size = source.size();
			Dir dircopy(dname / "bar");
			bool result = !dircopy.exist();
			Dir dest(dname);
			explorer.copy(testing_files_root / "bar", testing_files_root / "foo");
			result = result && source.exist() &&
				dircopy.exist() && Size == source.size();
			explorer.remove(testing_files_root / "foo/bar");
			ASSERT_BOOL(result);
		}),
		new UnitTest([]() {
			auto sname = testing_files_root / "bar";
			auto dname = testing_files_root / "foo";
			auto root = testing_files_root;
			Dir source(sname);
			size_t Size = source.size();
			Dir dest(dname);
			ContextMenu::move(source, dest);
			bool result = source.exist() && source.path() == testing_files_root / "foo/bar" && Size == source.size();
			ContextMenu::move(source, testing_files_root);
			result = result && source.exist() && source.path() == testing_files_root / "bar" && Size == source.size();
			ASSERT_BOOL(result);
		})
	}
};
#endif