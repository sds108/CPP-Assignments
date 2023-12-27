#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <limits> // needed for 'numeric_limits<>::max()'
#include <ios> // needed for 'streamsize'

class registry;
class folder;
class file;
class commandHandler;
class textEditor;

class registry {
private:
	std::vector<std::string> folders;
	std::vector<std::string> files;
	std::vector<folder*> folderPtrs;
	std::vector<file*> filePtrs;

public:
	// Does (File or Folder) Name already exist
	bool checkName (std::string name, std::vector<std::string>& type) {
		// Go through registry, try find name
		for (int i = 0; i < type.size(); i++) {
			if (name == type[i]) return true;
		}

		// If the 'for loop' doesn't find the name in the registry already
		return false;
	}

	// Does Folder pointer already exist?
	bool checkFolderPtr (folder* ptr) {
		// Go through registry, try find pointer
		for (int i = 0; i < folderPtrs.size(); i++) {
			if (ptr == folderPtrs[i]) return true;
		}

		// If the 'for loop' doesn't find the pointer in the registry already
		return false;
	}

	// Does File pointer already exist?
	bool checkFilePtr (file* ptr) {
		// Go through registry, try find pointer
		for (int i = 0; i < filePtrs.size(); i++) {
			if (ptr == filePtrs[i]) return true;
		}

		// If the 'for loop' doesn't find the pointer in the registry already
		return false;
	}

	// Fix Same Name problem
	std::string fixSameName (std::string name) {
		return (name + "_Diff");
	}

	// Find folder index from pointer
	int findFolderIndex (folder* ptr) {
		int index = -1;
		// Go through Registry
		for (int i = 0; i < folderPtrs.size(); i++) {
			if (ptr == folderPtrs[i]) index = i;
		}
		return index;
	}

	// Find file index
	int findFileIndex (file* ptr) {
		int index = -1;
		// Go through Registry
		for (int i = 0; i < filePtrs.size(); i++) {
			if (ptr == filePtrs[i]) index = i;
		}
		return index;
	}

	// Find File Name from pointer
	std::string findFileName (file* ptr) {
		if (checkFilePtr(ptr)) {
			return files[findFileIndex(ptr)];
		} else {
			return "Error";
		}
	}

	// Find Folder Name from pointer
	std::string findFolderName (folder* ptr) {
		if (checkFolderPtr(ptr)) {
			return folders[findFolderIndex(ptr)];
		} else {
			return "Error";
		}
	}

	// Register a New File
	void newFile (std::string name, file* ptr) {
		std::string finalName;
		
		// Check if pointer already exists
		if (checkFilePtr(ptr)) {
			std::cout << "Pointer is already Registered" << std::endl;
		} else {
			// Append Pointer to registry
			filePtrs.push_back(ptr);
			
			// Check if file name already exists
			if (checkName(name, files)) {
				finalName = name;
				while(checkName(finalName, files)) {
					finalName = fixSameName(finalName);
				}
			} else {
				finalName = name;
			}

			// Append folder name to registry
			files.push_back(finalName);
		}
	}

	// Register a New Folder
	void newFolder (std::string name, folder* ptr) {
		std::string finalName;
		//std::cout << "Registering new folder" << std::endl;

		// Check if pointer already exists
		if (checkFolderPtr(ptr)) {
			std::cout << "Pointer is already Registered" << std::endl;
		} else {
			// Append Pointer to registry
			folderPtrs.push_back(ptr);
			
			// Check if folder name already exists
			if (checkName(name, folders)) {
				finalName = name;
				while(checkName(finalName, folders)) {
					finalName = fixSameName(finalName);
				}
			} else {
				finalName = name;
			}

			// Append folder name to registry
			folders.push_back(finalName);
		}
	}

	// Change folder name
	void chFolderName (std::string newName, folder* ptr) {
		std::string finalName;
		
		if (checkFolderPtr(ptr)) {
			int index = findFolderIndex(ptr);
			
			// Final bug check
			if (index == -1) {
				std::cout << "Pointer index could not be found in Registry" << std::endl;
			} else {
				// Check if file name already exists
				if (checkName(newName, folders)) {
					finalName = fixSameName(newName);
				} else {
					finalName = newName;
				}

				// Finally change name
				folders[index] = finalName;
			}
			
		} else {
			std::cout << "Pointer is not Registered" << std::endl;
		}
	}

	// Change file name
	void chFileName (std::string newName, file* ptr) {
		std::string finalName;
		
		if (checkFilePtr(ptr)) {
			int index = findFileIndex(ptr);
			
			// Final bug check
			if (index == -1) {
				std::cout << "Pointer index could not be found in Registry" << std::endl;
			} else {
				// Check if file name already exists
				if (checkName(newName, files)) {
					finalName = fixSameName(newName);
				} else {
					finalName = newName;
				}

				// Finally change name
				files[index] = finalName;
			}
			
		} else {
			std::cout << "Pointer is not Registered" << std::endl;
		}
	}

	void printVectors () {
		// Files
		for (int i = 0; i < files.size(); i++) {
			std::cout << files[i] << std::endl;
		}

		// Folders
		for (int i = 0; i < folders.size(); i++) {
			std::cout << folders[i] << std::endl;
		}

		// Folder Pointers
		for (int i = 0; i < folderPtrs.size(); i++) {
			std::cout << folderPtrs[i] << std::endl;
		}
	}
};

class folder {
private:
	std::vector<folder*> folders;
	std::vector<file*> files;
	folder* parent;
	int layer;
	//std::string name = std::to_string(std::time(NULL) + (std::rand()%999999));


public:
	void printContents (registry* Registry) {
		std::cout << std::endl << "___Folders___" << std::endl;

		if (folders.size() > 0) {
			for (int i = 0; i < folders.size(); i++) {
				std::cout << Registry->findFolderName(folders[i]) << " " << folders[i] << std::endl;
			}
		} else {
			std::cout << "None" << std::endl;
		}

		std::cout << std::endl << "___Files___" << std::endl;

		if (files.size() > 0) {
			for (int i = 0; i < files.size(); i++) {
				std::cout << Registry->findFileName(files[i]) << std::endl;
			}
		} else {
			std::cout << "None" << std::endl;
		}

		std::cout << std::endl;
	}

	void setParent (folder* newParent) {
		parent = newParent;
	}

	void setLayer (int folderLayer) {
		layer = folderLayer;
	}

	folder* returnParent () {
		return parent;
	}

	int returnLayer () {
		return layer;
	}

	folder* returnFolderPointer (std::string folderName, registry* Registry) {
		for (int f = 0; f < folders.size(); f++) {
			if(folderName == Registry->findFolderName(folders[f])) {
				return folders[f];
			}
		}

		// in case it does not work
		return nullptr;
	}

	void recieveNewFolder (folder* newFolder) {
		if (newFolder != nullptr) {
			folders.push_back(newFolder);
		}
	}

	file* returnFilePointer (std::string name, registry* Registry) {
		for (int f = 0; f < files.size(); f++) {
			if(name == Registry->findFileName(files[f])) {
				return files[f];
			}
		}

		// in case it does not work
		return nullptr;
	}

	void recieveNewFile (file* newFile) {
		if (newFile != nullptr) {
			files.push_back(newFile);
		}
	}

	// Methods

	// Self Register
	//void selfRegister (registry* Registry, std::string name) {
	//	Registry->newFolder(name, this);
	//}
	
	// Return Name
	//std::string rName () { return name; }

	// Change Name
	//void chName(std::string newName);
};

class file {
private:
	// Variables
	folder* parent;
	std::string text;

public:
	// Methods

	// Set Parent Folder
	void setParent (folder* newParent) {
		parent = newParent;
	}

	// Return Text
	std::string returnString () {
		return text;
	}

	// Recieve changes to text
	void recieveTextEdit (std::string editedText) {
		text = editedText;
	}
};

class textEditor {
private:
	// Important
	//std::vector<std::string> asciiCharacters = {" ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?", "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\", "]", "^", "_", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", "~", "DEL"};
	//, "Ç", "ü", "é", "â", "ä", "à", "å", "ç", "ê", "ë", "è", "ï", "î", "ì", "Ä", "Å", "É", "æ", "Æ", "ô", "ö", "ò", "û", "ù", "ÿ", "Ö", "Ü", "ø", "£", "Ø", "×", "ƒ", "á", "í", "ó", "ú", "ñ", "Ñ", "ª", "º", "¿", "®", "¬", "½", "¼", "¡", "«", "»", "░", "▒", "▓", "│", "┤", "Á", "Â", "À", "©", "╣", "║", "╗", "╝", "¢", "¥", "┐", "└", "┴", "┬", "├", "─", "┼", "ã", "Ã", "╚", "╔", "╩", "╦", "╠", "═", "╬", "¤", "ð", "Ð", "Ê", "Ë", "È", "ı", "Í", "Î", "Ï", "┘", "┌", "█", "▄", "¦", "Ì", "▀", "Ó", "ß", "Ô", "Ò", "õ", "Õ", "µ", "þ", "Þ", "Ú", "Û", "Ù", "ý", "Ý", "¯", "´", "­", "±", "‗", "¾", "¶", "§", "÷", "¸", "°", "¨", "·", "¹", "³", "²", "■", "nbsp"};
	// Variables
	//file* currentTextFile;
	std::string extractedText;
	int index = 0;

public:
	// Methods
	// Initialize
	void Initialize (file* toEdit) {
		// Extract String from File
		extractedText = toEdit->returnString();

		std::string input;

		bool quit = false;
		//system ("/bin/stty -echo");

		while(!quit) {
			
			// Clear screen
			std::cout << "\x1B[2J\x1B[H";
			std::cout << "Left & Right Arrow to move the Cursor, Down Arrow for a new line\nInsert Key for Backspace, Delete Key for Delete" << std::endl;
			std::cout << "Home Key to Quick Save File, End Key to exit File\n" << std::endl;
			std::cout << "DO NOT TRY TO USE Enter, Backspace or Ctrl C\n" << std::endl;
			std::cout << "Index: " << index << "\n\n";

			// Turn off need for Enter, and turn off echo
			system ("/bin/stty raw");

			// Display top text (before Index)
			for (int i = 0; i < index; i++) {
				std::cout << extractedText[i];
			}
			// Display bottom text (after Index)
			std::cout << std::endl;
			for (int i = index; i < extractedText.size(); i++) {
				std::cout << extractedText[i];
			}
			input.clear();

			input = getc(stdin);

			// Look out for special characters
			if (input[0] == 27) { // ^[
				input += getc(stdin);
				input += getc(stdin);
				if (input[1] == 91) { // [
					if (input[2] == 67) { // C // Right Key
						if (index < extractedText.size())
						index++;
					}
					else if (input[2] == 66) { // B // Down Key // Used as New Line
						extractedText.insert(index, "\n");
						index++;
					}
					else if (input[2] == 68) { // D // Left Key
						if (index > 0) index--;
					}
					else if (input[2] == 72) { // H // Home Key // used to save the file
						toEdit->recieveTextEdit(extractedText);
					}
					else if (input[2] == 70) { // F // End Key // used to exit file
						// Return back to normal mode
						system ("/bin/stty cooked");
					
						// Check if user wants to save on exit
						std::cout << "\nWould you like to save the file before you exit ('yes' or 'no', or 'cancel' to cancel exiting): ";
						bool ready = false;
						std::string saveChar = "";
						std::cin >> saveChar;
						while (!ready) {
							std::cout << "SaveChar: " << saveChar << std::endl;
							if (saveChar == "yes") ready = true;
							else if (saveChar == "no") ready = true;
							else if (saveChar == "cancel") ready = true;
							else {
								std::cout << "\nPlease use 'yes' to save and exit, 'no' to exit without saving,\nor use 'cancel' to cancel leaving and continue editing the file: ";
								saveChar.clear();
								std::cin >> saveChar;
							}
						}
						
						if (saveChar == "yes") {
							toEdit->recieveTextEdit(extractedText);
							quit = true;
						}
						else if (saveChar == "no") {
							quit = true;
						}
						else if (saveChar == "cancel") {
							quit = false;
						}
						else {
							std::cout << "Some kind of problem occurred\n";
						}
					}
					else if (input[2] == 51) { // 3
						input += getc(stdin);
						if (input[3] == 126) { // ~ // Delete Key
							if (index < extractedText.size()) {
								extractedText.erase(extractedText.begin() + index, extractedText.begin() + index + 1);
							}
						}
					}
					else if (input[2] == 50) { // 2
						input += getc(stdin);
						if (input[3] == 126) { // ~ Insert Key // Used as Backspace
							if (index > 0) {
								extractedText.erase(extractedText.begin() + index - 1, extractedText.begin() + index);
								index--;
							}
						}
					}
				}
			}
			
			else {
				if (input[0] >= 32 && input[0] <= 127) {
					extractedText.insert(index, input);
					index++;
				}
			}

			// Return back to normal mode
			system ("/bin/stty cooked");
			/*
			if (input.size() == 1) {
				// Space Bar
				if (input[0] >= 32 && input[0] <= 127) {
					extractedText.insert(index, asciiCharacters[input[0]-31]);
					index++;
				}
			*/
				/*
				else if (input[0] == 33) {
					extractedText.insert(index, "!");
				}
				else if (input[0] == 34) {
					extractedText.insert(index, "\"");
				}
				else if (input[0] == 35) {
					extractedText.insert(index, "#");
				}
				else if (input[0] == 36) {
					extractedText.insert(index, "$");
				}
				else if (input[0] == 37) {
					extractedText.insert(index, "%");
				}
				else if (input[0] == 38) {
					extractedText.insert(index, "&");
				}
				else if (input[0] == 39) {
					extractedText.insert(index, "'");
				}
				else if (input[0] == 40) {
					extractedText.insert(index, "(");
				}
				else if (input[0] == 41) {
					extractedText.insert(index, ")");
				}
				else if (input[0] == 42) {
					extractedText.insert(index, "*");
				}
				else if (input[0] == 43) {
					extractedText.insert(index, "+");
				}
				else if (input[0] == 44) {
					extractedText.insert(index, ",");
				}
				else if (input[0] == 45) {
					extractedText.insert(index, "-");
				}
				else if (input[0] == 46) {
					extractedText.insert(index, ".");
				}
				else if (input[0] == 47) {
					extractedText.insert(index, "/");
				}
				else if (input[0] == 48) {
					extractedText.insert(index, "0");
				}
				else if (input[0] == 49) {
					extractedText.insert(index, "1");
				}
				else if (input[0] == 50) {
					extractedText.insert(index, "2");
				}
				else if (input[0] == 51) {
					extractedText.insert(index, "3");
				}
				else if (input[0] == 52) {
					extractedText.insert(index, "4");
				}
				else if (input[0] == 53) {
					extractedText.insert(index, "5");
				}
				else if (input[0] == 54) {
					extractedText.insert(index, "6");
				}
				else if (input[0] == 55) {
					extractedText.insert(index, "7");
				}
				else if (input[0] == 56) {
					extractedText.insert(index, "8");
				}
				else if (input[0] == 57) {
					extractedText.insert(index, "9");
				}
				else if (input[0] == 58) {
					extractedText.insert(index, ":");
				}
				else if (input[0] == 59) {
					extractedText.insert(index, ";");
				}
				else if (input[0] == 60) {
					extractedText.insert(index, "<");
				}
				else if (input[0] == 61) {
					extractedText.insert(index, "=");
				}
				else if (input[0] == 62) {
					extractedText.insert(index, ">");
				}
				else if (input[0] == 63) {
					extractedText.insert(index, "?");
				}
				else if (input[0] == 64) {
					extractedText.insert(index, "@");
				}
				else if (input[0] == 65) {
					extractedText.insert(index, "A");
				}
				else if (input[0] == 66) {
					extractedText.insert(index, "B");
				}
				else if (input[0] == 67) {
					extractedText.insert(index, "C");
				}
				else if (input[0] == 68) {
					extractedText.insert(index, "D");
				}
				else if (input[0] == 69) {
					extractedText.insert(index, "E");
				}
				else if (input[0] == 48) {
					extractedText.insert(index, "F");
				}
				else if (input[0] == 33) {
					extractedText.insert(index, "G");
				}
				else if (input[0] == 48) {
					extractedText.insert(index, "H");
				}
				else if (input[0] == 33) {
					extractedText.insert(index, "I");
				} */

			/*
			} else if (input.size() == 2) {
				
			} else if (input.size() == 3) {
				if (input[0] == 27 && input[1] == 91) {
					if (input[2] == 67) {
						if (index < extractedText.size())
						index++;
					}
					else if (input[2] == 68) {
						if (index > 0) index--;
					}
				}
			} else {
				std::cout << "Input Problem\n";
			}
		*/
		}

		
		//system ("/bin/stty echo");
		// Return back to normal mode
		system ("/bin/stty cooked");
		std::cout << "\x1B[2J\x1B[H";
		index = 0;
	}

};

class commandHandler {
private:
	folder* Origin;
	registry* Registry;
	textEditor* Editor;
	folder* currentFolder;
	std::vector<std::string> commandHistory;
	

public:
	// Set Initial Current Folder
	void Initialize (folder* OriginRef, registry* RegistryRef, textEditor* EditorRef) {
		Origin = OriginRef;
		Registry = RegistryRef;
		Editor = EditorRef;
		currentFolder = Origin;
	}

	// Handle Command
	void handleCommand (std::string commandChunk) { //, registry* Registry, folder* Origin, textEditor* Editor) {
		std::string command = "";
		std::string modifiers = "";
		int cutoff = 0;

		// Process Command
		for (int c = 0; c < commandChunk.size(); c++) {
			if (commandChunk[c] == ' ') {
				cutoff = c + 1;
				break;
			} else {
				command += commandChunk[c];
				cutoff = c + 1;
			}
		}

		for (int s = cutoff; s < commandChunk.size(); s++) {
			modifiers += commandChunk[s];
		}
		
		//std::cout << command << std::endl << modifiers << std::endl;

		// Deal with command
		if (command == "cd") {
			cd(modifiers); //, Registry, Origin);
			commandHistory.push_back(commandChunk); // Add Command to Hisory
		}
		else if (command == "ls") {
			ls(modifiers); //, Registry);
			commandHistory.push_back(commandChunk); // Add Command to Hisory
		}
		else if (command == "mkdir") {
			makeDir(modifiers); //, Registry, Origin);
			commandHistory.push_back(commandChunk); // Add Command to Hisory
		}
		else if (command == "clear") {
			cls();
			commandHistory.push_back(commandChunk); // Add Command to Hisory
		}
		else if (command == "help") {
			help();
			commandHistory.push_back(commandChunk); // Add Command to Hisory
		}
		else if (command == "edit") {
			EditFile(modifiers); //, Registry, Origin);
			commandHistory.push_back(commandChunk); // Add Command to Hisory
		}
		else if (command == "mkfile") {
			makeFile(modifiers); //, Registry, Origin);
			commandHistory.push_back(commandChunk); // Add Command to Hisory
		}
		else if (command == "print") {
			printFile(modifiers); //, Registry, Origin);
			commandHistory.push_back(commandChunk); // Add Command to Hisory
		}
		else if (command == "chist") cHistory(modifiers); //, Registry, Origin);
		//else if (command.size() == 3 && command[0] == 27 && command[1] == 91) arrow(command); // Left, Up, Right, Down
	}

	// Print Text File
	void printFile (std::string modifiers) { //, registry* Registry, folder* Origin) {
		std::string name = "";
		int cutoff = 0;

		if (modifiers.size() > 0) {
			// Get file name
			for (int c = 0; c < modifiers.size(); c++) {
				if (modifiers[c] == ' ') {
					cutoff = c + 1;
					break;
				} else {
					name += modifiers[c];
					cutoff = c + 1;
				}
			}
			
			// check if location specified
			std::string path = "";
			folder* fileLocation;
			if (cutoff < modifiers.size()) {
				for (int s = cutoff; s < modifiers.size(); s++) {
					path += modifiers[s];
				}
				if (path[0] == '/') {
					// remove '/'
					std::string editPath;
					for (int i = 1; i < path.size(); i++) {
						editPath += path[i];
					}
					fileLocation = derivePath(editPath, Origin);
				}

				else {
					fileLocation = derivePath(path, currentFolder);
				}
				
				// Last safety
				if (fileLocation == nullptr) {
					fileLocation = currentFolder;
				}
			}
			else {
				fileLocation = currentFolder;
			}

			// Search for file
			file* filePtr = fileLocation->returnFilePointer(name, Registry);

			// Check if valid
			if (filePtr == nullptr) {
				std::cout << "File not found, check your spelling for errors" << std::endl;
			} else {
				std::cout << std::endl << filePtr->returnString() << std::endl << std::endl;
			}
		}
			
		else {
			std::cout << "You need to specify the name of the file you want to print" << std::endl;
		}
	}

	// Edit Text
	void EditFile (std::string modifiers) { //, registry* Registry, folder* Origin) {
		std::string name = "";
		int cutoff = 0;

		if (modifiers.size() > 0) {
			// Get file name
			for (int c = 0; c < modifiers.size(); c++) {
				if (modifiers[c] == ' ') {
					cutoff = c + 1;
					break;
				} else {
					name += modifiers[c];
					cutoff = c + 1;
				}
			}
			
			// check if location specified
			std::string path = "";
			folder* fileLocation;
			if (cutoff < modifiers.size()) {
				for (int s = cutoff; s < modifiers.size(); s++) {
					path += modifiers[s];
				}
				if (path[0] == '/') {
					// remove '/'
					std::string editPath;
					for (int i = 1; i < path.size(); i++) {
						editPath += path[i];
					}
					fileLocation = derivePath(editPath, Origin);
				}

				else {
					fileLocation = derivePath(path, currentFolder);
				}
				
				// Last safety
				if (fileLocation == nullptr) {
					fileLocation = currentFolder;
				}
			}
			else {
				fileLocation = currentFolder;
			}

			// Search for file
			file* filePtr = fileLocation->returnFilePointer(name, Registry);

			// Check if valid
			if (filePtr == nullptr) {
				std::cout << "File not found, check your spelling for errors" << std::endl;
			} else {
				// Let's hope this works
				Editor->Initialize(filePtr);
			}
		}
			
		else {
			std::cout << "You need to specify the name of the file you want to edit" << std::endl;
		}
	}

	// Command History
	void cHistory (std::string modifiers) { //, registry* Registry, folder* Origin) {
		std::string numberStr;
		int numberInt = 5-1;
		int commandNumber = -1;
		int numberDisplayed = 0;
		if (modifiers.size() > 0) {
			for (int c = 0; c < modifiers.size(); c++) {
				numberStr += modifiers[c];
			}

			// Try convert to int
			try {
				numberInt = std::stoi(numberStr) - 1;
			} catch(std::invalid_argument) {
				numberInt = 5-1;
				std::cout << "\nInvalid number, showing up to " << numberInt + 1 << " commands instead\n";
			}
		}

		// Try print history
		std::cout << "\nCommand History\n";
		std::cout << "----------------\n";
		if (commandHistory.size() > 0) {
			if (commandHistory.size() > numberInt) {
				for (int i = commandHistory.size() - (numberInt + 1); i < commandHistory.size(); i++) {
					std::cout << commandHistory.size() - i << ") " << commandHistory[i] << std::endl;
					numberDisplayed++;
				}
			} else if (commandHistory.size() <= numberInt) {
				for (int i = 0; i < commandHistory.size(); i++) {
					std::cout << commandHistory.size() - i << ") " << commandHistory[i] << std::endl;
					numberDisplayed++;
				}
			}

			// Prompt for users input
			std::cout << "\nChoose the number of the command you want to run again\n(write '0' to cancel): ";
			if (!(std::cin >> commandNumber)) {
				// Clear buffer
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Please Enter a Numeric Value next time\n";
			} else if (commandNumber > numberDisplayed || (commandNumber < 1 && commandNumber != 0)) {
				std::cout << "Please Enter a number within the range shown next time\n";
			} else if (commandNumber == 0) {
				std::cout << "Cancelled\n";
			} else {
				std::cout << "\n";
				handleCommand(commandHistory[commandHistory.size() - commandNumber]);
			}
			
		} else {
			std::cout << "No History Found\n";
		}
	}

	// Help
	void help () {
		// Help Paragraph
		std::cout << "\nThis is a short guide to damOS\n--------------------------------------\n";
		std::cout << "To clear the command line, type 'clear'.\n";
		std::cout << "\nTo change directory or folder, use 'cd' with various modifiers.\n";
		std::cout << "'cd' on its own brings you to the Origin or Root of the system.\n";
		std::cout << "'cd -' brings you down a directory.\n";
		std::cout << "If you want to access a folder within your current directory, type 'cd folder_name/'.\n";
		std::cout << "And yes, that final '/' is necessary for the moment.\n";
		std::cout << "You can access further folders too, e.g. 'cd folder_name/next_folder/' this way you will cd to next_folder.\n";
		std::cout << "\nTo change directory to a specific directories outside of your current directory you have to specify\nthe full path you want to change to, you also have to put a '/' at the start of the path\nthis operation would look something like this: 'cd /Origin/folder1/folder2/'\nafter which you would move to folder2.\n";
		std::cout << "\nTo list folder contents, use 'ls'.\n";
		std::cout << "\nTo create a new folder or directory, use 'mkdir folder_name path'.\n";
		std::cout << "If you do not specify the path, the folder will be placed in your current directory.\n";
		std::cout << "Also the path syntax is the same as for the 'cd' command.\n";
		std::cout << "For paths accessible from your current location, the path should look like 'folder1/folder2/',\nwhere folder1 is inside your current directory, and the new folder will be saved to folder2.\n";
		std::cout << "\nTo create a new file, use 'mkfile file_name path',\npath is not required if you want to save to your current directory.\n";
		std::cout << "To edit the file, use 'edit file_name path',\npath is not necessary if the file is in your current directory.\n";
		std::cout << "To print the contents of the file use 'print file_name path',\nsame applies here, path is not necessary if the file is in your current directory.\n";
		std::cout << "\nYou can also view and reuse your command history using 'chist number_to_display',\nit is not necessary to provide a number, it shows 5 by default.\n";
		
		std::cout << "\nFor now there is not much else you can do with this system, but there is many good things to come.\n\n";
	}

	// Clear screen
	void cls () {
		std::cout << "\x1B[2J\x1B[H";
	}

	// Derive Path
	folder* derivePath (std::string path, folder* startingFolder) {
		std::string nextName;
		folder* nextFolder = startingFolder;

		for (int i = 0; i < path.size(); i++) {
			if (path[i] == '/') {
				if (nextName != "Origin") {
					nextFolder = nextFolder->returnFolderPointer(nextName, Registry);
				}
				
				if (nextFolder == nullptr) {
					std::cout << "Could not find path '" << path << "'" << std::endl;
					return nullptr;
				}
				
				nextName.clear();
			}
			else {
				nextName += path[i];
			}
		}

		// if the program has made it this far, assign the new location
		return nextFolder;
		
		/*
		// derive path
		std::vector<std::string> actualPath;
		int marker = 0;
		std::string newPath = "";
		while (marker <= path.size() - 1) {
			newPath.clear();
			for (int i = 0; i < path.size(); i++) {
				//std::cout << "Marker " << marker << std::endl;
				if (path[i] == '/') {
					marker++;
					break;
				} else {
					newPath += path[i];
					marker++;
				}
			}
			actualPath.push_back(newPath);
		}

		//std::cout << actualPath[0] << std::endl;
			
		folder* currentPath = Origin;
		folder* nextPath = currentPath;
		for (int i = 0; i < actualPath.size(); i++) {
			nextPath = currentPath->returnFolderPointer(actualPath[i], Registry);
			currentPath = nextPath;
			if (currentPath == nullptr) {
				std::cout << "Could not find path '" << actualPath[i] << "'" << std::endl;
				return nullptr;
				break;
			}
		}
		*/
	}

	// Change Directory
	void cd (std::string path) { //, registry* Registry, folder* Origin) {		
	
		// origin
		if (path.size() == 0) {
			currentFolder = Origin;
			std::cout << "Changing directory to the Origin" << std::endl;
		}
	
		// down directory
		else if (path.size() == 1 && path[0] == '-') {
			currentFolder = currentFolder->returnParent();
			std::cout << "Moving down one directory" << std::endl;
		}
			
		// actual change of directory to new path
		else if (path[0] == '/') {
			
			// remove '/'
			std::string editPath;
			for (int i = 1; i < path.size(); i++) {
				editPath += path[i];
			}
			
			// Derive Path
			folder* derivedPath = derivePath(editPath, Origin);
			
			// assign new path
			if (derivedPath == nullptr) {
				std::cout << "Could not derive path correctly" << std::endl;
			} else {
				currentFolder = derivedPath;
				//std::cout << "You should now be in your new folder: " << currentFolder << std::endl;
			}
		}

		// move up directory
		else {
			/* derive path
			std::vector<std::string> actualPath;
			int marker = 0;
			std::string newPath = "";
			while (marker <= path.size() - 1) {
				newPath.clear();
				for (int i = 0; i < path.size(); i++) {
					//std::cout << "Marker " << marker << std::endl;
					if (path[i] == '/') {
						marker++;
						break;
					} else {
						newPath += path[i];
						marker++;
					}
				}
				actualPath.push_back(newPath);
			}

			//std::cout << actualPath[0] << std::endl;
			
			folder* currentPath = Origin;
			for (int i = 0; i < actualPath.size(); i++) {
				currentPath = currentPath->returnFolderPointer(actualPath[i], Registry);
				if (currentPath == nullptr) {
					std::cout << "Could not find path '" << actualPath[i] << "'" << std::endl;
					break;
				}
			}
			*/
			// Derive Path
			folder* derivedPath = derivePath(path, currentFolder);
			
			// assign new path
			if (derivedPath == nullptr) {
				std::cout << "Could not derive path correctly" << std::endl;
			} else {
				currentFolder = derivedPath;
				//std::cout << "You should now be in your new folder: " << currentFolder << std::endl;
			}
		}
	}

	// List folder contents
	void ls (std::string modifiers) { //, registry* Registry) {
		// List function in current folder
		currentFolder->printContents(Registry);
	}
	
	// Make new directory
	void makeDir (std::string modifiers) { //, registry* Registry, folder* Origin) {
		std::string newName = "";
		int cutoff = 0;

		if (modifiers.size() > 0) {
			// Get new directory name
			for (int c = 0; c < modifiers.size(); c++) {
				if (modifiers[c] == ' ') {
					cutoff = c + 1;
					break;
				} else {
					newName += modifiers[c];
					cutoff = c + 1;
				}
			}
	
			//std::cout << "New Directory Name: " << newName << std::endl;
			
			// check if location specified
			std::string path = "";
			folder* newDirLocation;
			if (cutoff < modifiers.size()) {
				for (int s = cutoff; s < modifiers.size(); s++) {
					path += modifiers[s];
				}
				if (path[0] == '/') {
					// remove '/'
					std::string editPath;
					for (int i = 1; i < path.size(); i++) {
						editPath += path[i];
					}
					newDirLocation = derivePath(editPath, Origin);
				}

				else {
					newDirLocation = derivePath(path, currentFolder);
				}
				
				// Last safety
				if (newDirLocation == nullptr) {
					newDirLocation = currentFolder;
				}
			}
			else {
				newDirLocation = currentFolder;
			}
	
			// Make new folder
			folder* newDirPtr = new(std::nothrow) folder;
			Registry->newFolder(newName, newDirPtr);
			newDirPtr->setParent(newDirLocation);
			newDirPtr->setLayer(newDirLocation->returnLayer() + 1);
			newDirLocation->recieveNewFolder(newDirPtr);
		}

		else {
			std::cout << "You need to provide a name for your new directory" << std::endl;
		}
	}

	// Print Directory location
	void printLocation () { //(registry* Registry, folder* Origin) {
		folder* nextParent = currentFolder;
		std::vector<folder*> printOrder;

		// Get print order
		for (int i = 0; i <= currentFolder->returnLayer(); i++)  {
			printOrder.push_back(nextParent);
			nextParent = nextParent->returnParent();
		}

		// Print Location
		for (int i = printOrder.size() - 1; i >= 0; i--)  {
			std::cout << "/" << Registry->findFolderName(printOrder[i]);
		}
		
		std::cout << "> ";
	}

	// Make new file
	void makeFile (std::string modifiers) { //, registry* Registry, folder* Origin) {
		std::string newName = "";
		int cutoff = 0;

		if (modifiers.size() > 0) {
			// Get new directory name
			for (int c = 0; c < modifiers.size(); c++) {
				if (modifiers[c] == ' ') {
					cutoff = c + 1;
					break;
				} else {
					newName += modifiers[c];
					cutoff = c + 1;
				}
			}

			// check if location specified
			std::string path = "";
			folder* newDirLocation;
			if (cutoff < modifiers.size()) {
				for (int s = cutoff; s < modifiers.size(); s++) {
					path += modifiers[s];
				}
				if (path[0] == '/') {
					// remove '/'
					std::string editPath;
					for (int i = 1; i < path.size(); i++) {
						editPath += path[i];
					}
					newDirLocation = derivePath(editPath, Origin);
				}

				else {
					newDirLocation = derivePath(path, currentFolder);
				}
				
				// Last safety
				if (newDirLocation == nullptr) {
					newDirLocation = currentFolder;
				}
			}
			else {
				newDirLocation = currentFolder;
			}
	
			// Make new file
			file* newFilePtr = new(std::nothrow) file;
			Registry->newFile(newName, newFilePtr);
			newFilePtr->setParent(newDirLocation);
			//newFilePtr->setLayer(newDirLocation->returnLayer() + 1);
			newDirLocation->recieveNewFile(newFilePtr);
		}

		else {
			std::cout << "You need to provide a name for your new file" << std::endl;
		}
	}
};

int main() {
	// Set Seed
	std::srand(std::time(NULL));
	
	// Create a Registry
	registry Registry;

	// Create the Origin Folder
	folder Origin;

	// Create Text Editor
	textEditor Editor;

	// Prepare Origin
	Registry.newFolder("Origin", &Origin);
	Origin.setParent(&Origin);
	Origin.setLayer(0);

	// CLI Variables
	std::string currentDirectory;
	folder* currentFolder = &Origin;
	folder* nextDir = currentFolder;
	std::string cliInput;
	bool inApplication = false;
	commandHandler cHandler;

	// Initialize Command Handler
	cHandler.Initialize(&Origin, &Registry, &Editor);
	
	// Program Start
	while(true) {
		if (inApplication) {
			
		} else {
		
			//currentDirectory = Registry.findFolderName(currentFolder);

			//std::cout << currentFolder << " " << currentDirectory << std::endl;
			
	
			// Print directory displayer
			//std::vector<std::string> printOrder;
			//std::string lastDir;
			//nextDir = currentFolder;
			/*
			while (nextDir != &Origin) {
				std::cout << " 2 " << nextDir << std::endl;
				
				lastDir = Registry.findFolderName(nextDir);
				std::cout << " 3 " << lastDir << std::endl;
				
				printOrder.push_back(lastDir);
				nextDir = nextDir->returnParent();
				std::cout << " 4 " << nextDir << " = " << &Origin << std::endl;

				if (nextDir != &Origin) {
					std::cout << " 5 " << "False";
				}
			}
	
			// Print Directory
			std::cout << "/";
			for (int d = 0; d < printOrder.size(); d++) {
				std::cout << printOrder[printOrder.size()-d] << "/";
			}
			*/
			//std::cout << currentDirectory;
			//std::cout << "> ";
			cHandler.printLocation();
			
			cliInput.clear();
			
			getline(std::cin, cliInput);

			cHandler.handleCommand(cliInput);
		}
	}
}