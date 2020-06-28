#pragma once
#include "../../core/testing/module_test.h"
#include "../../core/testing/assert.h"
using namespace Core::Testing;
using namespace Core::Filesystem;
using namespace Core::Exception;
#include "../../core/filesystem/file.h"
#include "../../core/filesystem/dir.h"
#include "../../core/filesystem/context_menu.h"
#include "../../core/filesystem/explorer.h"

const Path testing_files_root = "./test/files";

ModuleTest FilesystemUnitTests = {
	"Filesystem",
	{
		new unit_equal("file descryptor constructing with file path", []() {
			const auto p = testing_files_root / "1.png";
			FileDescryptor f(p);
			return AssertEqual(f.path(), p);
		}),
		new unit_exception("file descryptor constructing with dir path",
			Core::Exception::invalid_argument("path contains dir not a file"), 
			[]() {
			const auto dir = testing_files_root;
			FileDescryptor file(dir);
		}),
		new unit_exception("file descryptor constructing with empty path",
			Core::Exception::invalid_argument("path is empty"),
			[]() {
			FileDescryptor file("");
		}),
		new unit_exception("file descryptor set dir path",
			Core::Exception::invalid_argument("path contains dir not a file"),
			[]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			file.path(testing_files_root);
		}),
		new unit_exception("file descryptor set empty path",
			Core::Exception::invalid_argument("path is empty"),
			[]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			file.path("");
		}),
		new unit_bool("checking unexisted file existing", 
			[]() {
			const auto unexisted_file = "akldjgoieuriaikojdbafhb.txt";
			FileDescryptor file(unexisted_file);
			return !file.exist();
		}),
		new unit_bool("checking existed file existing ",
			[]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			return file.exist();
		}),
		new unit_equal("checking unexisted file path", 
			[]() {
			const auto unexisted_file = "akldjgoieuriaikojdbafhb.txt";
			FileDescryptor file(unexisted_file);
			return AssertEqual(file.path(), unexisted_file);
		}),
		new unit_equal("checking existed file path", 
			[]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			return AssertEqual(file.path(), name);
		}),
		new unit_equal("checking existed file size", 
			[]() {
			const auto name = testing_files_root / "bar/1.jpg";
			FileDescryptor file(name);
			return AssertEqual(file.size(), fs::file_size(name));
		}),
		new unit_exception("checking unexisted file size must throwing an exception",
			file_not_exist("checking file size"),
			[]() {
			const auto unexisted_file = "akldjgoieuriaikojdbafhb.txt";
			FileDescryptor file(unexisted_file);
			file.size();
		}),
		new unit_exception("deleting unexisted file",
			file_not_exist("deleting unexisted file"),
			[]() {
			const auto unexisted_file = "akldjgoieuriaikojdbafhb.txt";
			FileDescryptor file(unexisted_file);
			file.remove();
		}),
		new unit_bool("deleting existed file",
			[]() {
			const auto name = testing_files_root / "new_file.txt";
			std::ofstream new_file(testing_files_root / "new_file.txt", std::ios::binary);
			new_file.close();
			FileDescryptor file(name);
			file.remove();
			return !file.exist();
		}),
		new unit_exception("create existed file",
			file_already_exist("creating new file"),
			[]() {
			const auto name = testing_files_root / "bar/1.jpg";
			FileDescryptor file(name);
			file.create();
		}),
		new unit_bool("create unexisted file",
			[]() {
			const auto name = testing_files_root / "new_file.txt";
			FileDescryptor file(name);
			file.create();
			bool result = file.exist();
			file.remove();
			return result;
		}),
		new unit_equal("changing file path",
			[]() {
			const auto name = testing_files_root / "some_file.txt";
			FileDescryptor file(name);
			file.path(testing_files_root / "some_file.qwerty");
			return AssertEqual(file.path(), testing_files_root / "some_file.qwerty");
		}),

		new unit_equal("read data block of readable file",
			[]() {
			auto name = testing_files_root / "simple text.txt";
			ReadableFile simpleText(name);
			simpleText.open();
			std::vector<Byte> file = simpleText.read(4, 7);
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			return AssertEqual(result, "text");
		}),
		new unit_equal("read data block of file",
			[]() {
			auto name = testing_files_root / "simple text.txt";
			File simpleText(name);
			simpleText.open4read();
			std::vector<Byte> file = simpleText.read(4, 7);
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			return AssertEqual(result, "text");
		}),

		new unit_equal("explorer descryptor default constructing",
			[]() {
			Explorer explorer;
			return AssertEqual(explorer.path(), fs::current_path());
		}),
		new unit_equal("directory descryptor constructing with dir path",
			[]() {
			const auto p = testing_files_root;
			DirDescryptor dir(p);
			return AssertEqual(dir.path(), p);
		}),
		new unit_exception("directory descryptor constructing with existing file path",
			Core::Exception::invalid_argument("path contains file not a dir"),
			[]() {
			DirDescryptor dir(testing_files_root / "bar/1.jpg");
		}),
		new unit_exception("directory descryptor constructing with empty path",
			Core::Exception::invalid_argument("path is empty"),
			[]() {
			DirDescryptor dir("");
		}),
		new unit_exception("directory descryptor set file path",
			Core::Exception::invalid_argument("path contains file not a dir"),
			[]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			dir.path(testing_files_root / "bar/1.jpg");
		}),
		new unit_exception("directory descryptor set empty path",
			Core::Exception::invalid_argument("path is empty"),
			[]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			dir.path("");
		}),
		new unit_bool("checking unexisted directory existing",
			[]() {
			const auto unexisted_directory = "akldjgoieuriaikojdbafhb";
			DirDescryptor dir(unexisted_directory);
			return !dir.exist();
		}),
		new unit_bool("checking existed directory existing",
			[]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			return dir.exist();
		}),
		new unit_equal("checking unexisted directory path",
			[]() {
			const auto unexisted_directory = "akldjgoieuriaikojdbafhb";
			DirDescryptor dir(unexisted_directory);
			return AssertEqual(dir.path(), unexisted_directory);
		}),
		new unit_equal("checking existed directory path",
			[]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			return AssertEqual(dir.path(), name);
		}),
		new unit_equal("checking existed directory size",
			[]() {
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
			return AssertEqual(dir.size(), result);
		}),
		new unit_exception("checking unexisted directory size",
			dir_not_exist("checking dir size"),
			[]() {
			const auto unexisted_directory = "akldjgoieuriaikojdbafhb";
			DirDescryptor dir(unexisted_directory);
			dir.size();
		}),
		new unit_exception("create existed directory",
			dir_already_exist("creating new dir"),
			[]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			dir.create();
		}),
		new unit_bool("create unexisted directory",
			[]() {
			const auto name = testing_files_root / "some_directory";
			DirDescryptor dir(name);
			dir.create();
			bool result = dir.exist();
			dir.remove();
			return result;
		}),
		new unit_exception("deleting unexisted directory",
			dir_not_exist("deleting unexisted dir"),
			[]() {
			const auto unexisted_directory = "akldjgoieuriaikojdbafhb";
			DirDescryptor dir(unexisted_directory);
			dir.remove();
		}),
		new unit_bool("deleting existed directory",
			[]() {
			const auto name = testing_files_root / "new_dir";
			DirDescryptor new_dir(name);
			new_dir.create();
			DirDescryptor dir(name);
			dir.remove();
			return !dir.exist();
		}),
		new unit_equal("changing dir path",
			[]() {
			const auto name = testing_files_root / "some_dir";
			DirDescryptor dir(name);
			dir.path(testing_files_root);
			return AssertEqual(dir.path(), testing_files_root);
		}),

		new unit_bool("context menu create and remove files",
			[]() {
			const auto name = testing_files_root / "some_file.qwerty";
			FileDescryptor file(name);
			ContextMenu::create(file);
			bool result = file.exist();
			ContextMenu::remove(file);
			result = result && !file.exist();
			return result;
		}),
		new unit_bool("context menu create and remove empty dir",
			[]() {
			const auto name = testing_files_root / "new_dir";
			DirDescryptor dir(name);
			ContextMenu::create(dir);
			bool result = dir.exist();
			ContextMenu::remove(dir);
			result = result && !dir.exist();
			return result;
		}),
		new unit_bool("context menu checking existing of unexisting dir",
			[]() {
			const auto name = testing_files_root / "un/existed/dir";
			DirDescryptor dir(name);
			return !ContextMenu::exist(dir);
		}),
		new unit_bool("context menu checking existing of existing dir",
			[]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			return ContextMenu::exist(dir);
		}),
		new unit_bool("context menu checking existing of unexisting file",
			[]() {
			const auto name = testing_files_root / "some_unexisting file.hpy";
			FileDescryptor file(name);
			return !ContextMenu::exist(file);
		}),
		new unit_bool("context menu checking existing of existing file",
			[]() {
			const auto name = testing_files_root / "1.jpg";
			FileDescryptor file(name);
			return ContextMenu::exist(file);
		}),
		new unit_equal("context menu checking size of existing dir",
			[]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			return AssertEqual(ContextMenu::size(dir), dir.size());
		}),
		new unit_equal("context menu checking size of existing file",
			[]() {
			const auto name = testing_files_root / "bar/1.jpg";
			FileDescryptor file(name);
			return AssertEqual(ContextMenu::size(file), file.size());
		}),
		new unit_exception("context menu checking size of unexisting dir",
			dir_not_exist("checking dir size"),
			[]() {
			const auto name = testing_files_root / "unexisted---dir";
			DirDescryptor dir(name);
			ContextMenu::size(dir);
		}),
		new unit_exception("context menu create existing file",
			file_already_exist("creating new file"),
			[]() {
			const auto name = testing_files_root / "bar/1.jpg";
			FileDescryptor file(name);
			ContextMenu::create(file);
		}),
		new unit_exception("context menu create existing dir",
			dir_already_exist("creating new dir"),
			[]() {
			const auto name = testing_files_root;
			DirDescryptor dir(name);
			ContextMenu::create(dir);
		}),
		new unit_exception("context menu remove unexisting file",
			file_not_exist("deleting unexisted file"),
			[]() {
			const auto name = testing_files_root / "non-existing-file";
			FileDescryptor file(name);
			ContextMenu::remove(file);
		}),
		new unit_exception("context menu remove unexisting dir",
			dir_not_exist("deleting unexisted dir"),
			[]() {
			const auto name = testing_files_root / "non-existing-file";
			DirDescryptor dir(name);
			ContextMenu::remove(dir);
		}),
		new unit_bool("context menu remove non-empty dir",
			[]() {
			auto name = testing_files_root / "new_dir";
			DirDescryptor dir(name);
			ContextMenu::create(dir);
			name /= "newfile.txt";
			FileDescryptor file(name);
			ContextMenu::create(file);
			ContextMenu::remove(dir);
			return !file.exist() && !dir.exist();
		}),
		new unit_equal("context menu listing dir descryptor",
			[]() {
			auto name = testing_files_root;
			DirDescryptor dir(name);
			auto listing = ContextMenu::listing(dir);
			size_t count = listing.dirs.size() + listing.files.size();
			return AssertEqual(count, 9);
		}),
		new unit_equal("context menu listing empty dir descryptor",
			[]() {
			auto name = testing_files_root / "new_dir";
			DirDescryptor dir(name);
			dir.create();
			auto listing = ContextMenu::listing(dir);
			dir.remove();
			size_t count = listing.dirs.size() + listing.files.size();
			return AssertEqual(count, 0);
		}),
		new unit_equal("context menu listing dir",
			[]() {
			auto name = testing_files_root;
			Dir dir(name);
			auto listing = ContextMenu::listing(dir);
			size_t count = listing.dirs.size() + listing.files.size();
			return AssertEqual(count, 9);
		}),
		new unit_equal("context menu listing empty dir",
			[]() {
			auto name = testing_files_root / "new_dir";
			Dir dir(name);
			dir.create();
			auto listing = ContextMenu::listing(dir);
			dir.remove();
			size_t count = listing.dirs.size() + listing.files.size();
			return AssertEqual(count, 0);
		}),
		new unit_equal("context menu read full file",
			[]() {
			auto name = testing_files_root / "simple text.txt";
			File simpleText(name);
			simpleText.open4read();
			std::vector<Byte> file;
			ContextMenu::read(simpleText, [&file](std::vector<Byte> d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			return AssertEqual(result, "simple text data");
		}),
		new unit_equal("context menu read blocks file",
			[]() {
			auto name = testing_files_root / "simple text.txt";
			File simpleText(name);
			simpleText.open4read();
			std::vector<Byte> file;
			ContextMenu::read(simpleText, 4, [&file](std::vector<Byte> d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			return AssertEqual(result, "simple text data");
		}),
		new unit_equal("context menu read so big block of file",
			[]() {
			auto name = testing_files_root / "simple text.txt";
			File simpleText(name);
			simpleText.open4read();
			std::vector<Byte> file;
			ContextMenu::read(simpleText, 100500, [&file](std::vector<Byte> d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			return AssertEqual(result, "simple text data");
		}),
		new unit_bool("context menu move file to another folder and back",
			[]() {
			auto fname = testing_files_root / "simple text.txt";
			auto dname = testing_files_root / "bar";
			auto root = testing_files_root;
			File file(fname);
			Dir dir(dname);
			ContextMenu::move(file, dir);
			bool result = file.exist() && file.path() == testing_files_root / "bar\\simple text.txt";
			ContextMenu::move(file, testing_files_root);
			result = result && file.exist() && file.path() == testing_files_root / "simple text.txt";
			return result;
		}),
		new unit_bool("context menu copy file to another folder",
			[]() {
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
			return result;
		}),
		new unit_bool("context menu create empty dir, move to another folder and delete it",
			[]() {
			auto sname = testing_files_root / "new_dir";
			auto dname = testing_files_root / "bar";
			Dir source(sname);
			ContextMenu::create(source);
			Dir dest(dname);
			ContextMenu::move(source, dest);
			bool result = source.exist() && source.path() == testing_files_root / "bar\\new_dir";
			ContextMenu::remove(source);
			return result;
		}),
		new unit_bool("context menu move dir to another folder and back",
			[]() {
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
			return result;
		}),
		new unit_bool("context menu copy dir to another folder and remove copy",
			[]() {
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
			return result;
		}),
		new unit_exception("context menu listing unexisted dir",
			dir_not_exist("listing unexisted dir"),
			[]() {
			auto name = testing_files_root / "unexisteddir";
			Dir dir(name);
			ContextMenu::listing(dir);
		}),
		new unit_exception("open for read empty file",
			non_readable("open empty file for reading"),
			[]() {
			auto name = testing_files_root / "foo/empty-file";
			File simpleText(name);
			simpleText.open4read();
		}),
		new unit_exception("open for read unexisted file",
			file_not_exist("open file for reading"),
			[]() {
			auto name = testing_files_root / "txt";
			File simpleText(name);
			simpleText.open4read();
		}),
		new unit_exception("context menu moving unexisted file",
			file_not_exist("source file not found when moving"),
			[]() {
			auto name = testing_files_root / "txt";
			File file(name);
			ContextMenu::move(file, { "path/to/dir" });
		}),
		new unit_exception("context menu moving unexisted dir",
			dir_not_exist("source folder not found when moving"),
			[]() {
			auto name = testing_files_root / "txt";
			Dir dir(name);
			ContextMenu::move(dir, { "path/to/dir" });
		}),
		new unit_exception("context menu moving existed dir to unexisted folder",
			dir_not_exist("destination not found when moving"),
			[]() {
			auto name = testing_files_root / "foo";
			Dir dir(name);
			ContextMenu::move(dir, { "path/to/dir" });
		}),
		new unit_exception("context menu moving existed file to unexisted folder",
			dir_not_exist("destination not found when moving"),
			[]() {
			auto name = testing_files_root / "bar/1.jpg";
			File file(name);
			ContextMenu::move(file, { "path/to/dir" });
		}),
		new unit_exception("context menu moving dir to folder where dir with same name already existed",
			dir_already_exist("moving destination already contains source folder"),
			[]() {
			auto name = testing_files_root / "bar";
			Dir dir(name);
			ContextMenu::move(dir, { testing_files_root });
		}),
		new unit_exception("context menu moving file to folder where file with same name already existed",
			file_already_exist("moving destination already contains source file"),
			[]() {
			auto name = testing_files_root / "bar/1.jpg";
			File file(name);
			ContextMenu::move(file, { testing_files_root / "bar" });
		}),

		new unit_bool("explorer create and remove file",
			[]() {
			const auto fname = testing_files_root / "some_file.qwerty";
			Explorer explorer;
			explorer.mkfile(fname);
			bool result = File(fname).exist();
			explorer.remove(fname);
			result = result && !File(fname).exist();
			return result;
		}),
		new unit_bool("explorer create and remove empty dir",
			[]() {
			const auto dname = testing_files_root / "new_dir";
			Explorer explorer;
			explorer.mkdir(dname);
			bool result = Dir(dname).exist();
			explorer.remove(dname);
			result = result && !Dir(dname).exist();
			return result;
		}),
		new unit_bool("explorer checking existing of unexisting dir",
			[]() {
			const auto name = testing_files_root / "un/existed/dir";
			Explorer explorer;
			return !explorer.exist(name);
		}),
		new unit_bool("explorer checking existing of existing dir",
			[]() {
			const auto name = testing_files_root;
			Explorer explorer;
			return explorer.exist(name);
		}),
		new unit_bool("explorer checking existing of unexisting file",
			[]() {
			const auto name = testing_files_root / "some_unexisting file.hpy";
			Explorer explorer;
			return !explorer.exist(name);
		}),
		new unit_bool("explorer checking existing of existing file",
			[]() {
			const auto name = testing_files_root / "1.jpg";
			Explorer explorer;
			return explorer.exist(name);
		}),
		new unit_equal("explorer checking size of existing dir",
			[]() {
			const auto name = testing_files_root;
			Explorer explorer;
			DirDescryptor dir(name);
			return AssertEqual(explorer.size(name), dir.size());
		}),
		new unit_equal("explorer checking size of existing file",
			[]() {
			const auto name = testing_files_root / "bar/1.jpg";
			Explorer explorer;
			FileDescryptor file(name);
			return AssertEqual(explorer.size(name), file.size());
		}),
		new unit_exception("explorer checking size of unexisting dir",
			file_not_exist("explorer checking size"),
			[]() {
			const auto name = testing_files_root / "unexisted---dir";
			Explorer explorer;
			explorer.size(name);
		}),
		new unit_exception("explorer create existing file",
			file_already_exist("creating new file"),
			[]() {
			const auto name = testing_files_root / "bar/1.jpg";
			Explorer explorer;
			explorer.mkfile(name);
		}),
		new unit_exception("explorer create existing dir",
			dir_already_exist("creating new dir"),
			[]() {
			const auto name = testing_files_root;
			Explorer explorer;
			explorer.mkdir(name);
		}),
		new unit_exception("explorer remove unexisting file or dir",
			file_not_exist("explorer deleting unexisted file or dir"),
			[]() {
			const auto name = testing_files_root / "non-existing-file";
			Explorer explorer;
			explorer.remove(name);
		}),
		new unit_bool("explorer remove non-empty dir",
			[]() {
			auto name = testing_files_root / "new_dir";
			Explorer explorer;
			DirDescryptor dir(name);
			explorer.mkdir(name);
			name /= "newfile.txt";
			FileDescryptor file(name);
			explorer.mkfile(name);
			explorer.remove(dir.path());
			return !file.exist() && !dir.exist();
		}),
		new unit_equal("explorer listing dir descryptor",
			[]() {
			auto name = testing_files_root;
			Explorer explorer;
			auto listing = explorer.listing(name);
			size_t count = listing.dirs.size() + listing.files.size();
			return AssertEqual(count, 9);
		}),
		new unit_equal("explorer listing empty dir descryptor",
			[]() {
			auto name = testing_files_root / "new_dir";
			DirDescryptor dir(name);
			Explorer explorer;
			explorer.mkdir(name);
			auto listing = explorer.listing(name);
			dir.remove();
			size_t count = listing.dirs.size() + listing.files.size();
			return AssertEqual(count, 0);
		}),
		new unit_equal("explorer listing dir",
			[]() {
			auto name = testing_files_root;
			Explorer explorer;
			auto listing = explorer.listing(name);
			size_t count = listing.dirs.size() + listing.files.size();
			return AssertEqual(count, 9);
		}),
		new unit_equal("explorer listing empty dir",
			[]() {
			auto name = testing_files_root / "new_dir";
			Explorer explorer;
			Dir dir(name);
			dir.create();
			auto listing = explorer.listing(name);
			dir.remove();
			size_t count = listing.dirs.size() + listing.files.size();
			return AssertEqual(count, 0);
		}),
		new unit_equal("explorer read full file",
			[]() {
			auto name = testing_files_root / "simple text.txt";
			Explorer explorer;
			std::vector<Byte> file = explorer.read(name);
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			return AssertEqual(result, "simple text data");
		}),
		new unit_equal("explorer read blocks file",
			[]() {
			auto name = testing_files_root / "simple text.txt";
			Explorer explorer;
			std::vector<Byte> file;
			explorer.read(name, 4, [&file](std::vector<Byte> d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			return AssertEqual(result, "simple text data");
		}),
		new unit_equal("explorer read so big block of file",
			[]() {
			auto name = testing_files_root / "simple text.txt";
			Explorer explorer;
			std::vector<Byte> file;
			explorer.read(name, 100500, [&file](std::vector<Byte> d) {
				std::copy(d.begin(), d.end(), back_inserter(file));
			});
			std::string result = file.data();
			result.erase(result.begin() + file.size(), result.end());
			return AssertEqual(result, "simple text data");
		}),
		new unit_bool("explorer move file to another folder and back",
			[]() {
			auto fname = testing_files_root / "simple text.txt";
			auto dname = testing_files_root / "bar";
			auto root = testing_files_root;
			Explorer explorer;
			File file(fname);
			Dir dir(dname);
			explorer.move(testing_files_root / "simple text.txt", testing_files_root / "bar");
			bool result = file.exist();
			explorer.move(testing_files_root / "bar/simple text.txt", testing_files_root);
			result = result && file.exist();
			return result;
		}),
		new unit_bool("explorer copy file to another folder",
			[]() {
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
			return result;
		}),
		new unit_bool("explorer create empty dir, move to another folder and delete it",
			[]() {
			auto sname = testing_files_root / "new_dir";
			auto dname = testing_files_root / "bar";
			Explorer explorer;
			Dir source(sname);
			explorer.mkdir(testing_files_root / "new_dir");
			Dir dest(testing_files_root / "bar");
			explorer.move(testing_files_root / "new_dir", testing_files_root / "bar");
			bool result = source.exist();
			explorer.remove(testing_files_root / "bar/new_dir");
			return result;
		}),
		new unit_bool("explorer move dir to another folder and back",
			[]() {
			auto sname = testing_files_root / "bar";
			auto dname = testing_files_root / "foo";
			auto root = testing_files_root;
			Explorer explorer;
			Dir source(sname);
			size_t Size = source.size();
			Dir dest(dname);
			explorer.move(testing_files_root / "bar", testing_files_root / "foo");
			bool result = source.exist() && Size == source.size();
			explorer.move(testing_files_root / "foo/bar", testing_files_root);
			result = result && source.exist() && Size == source.size();
			return result;
		}),
		new unit_bool("explorer copy dir to another folder and remove copy",
			[]() {
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
			return result;
		}),
	}
};
