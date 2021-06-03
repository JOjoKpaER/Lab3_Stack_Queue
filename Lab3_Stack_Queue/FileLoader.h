#pragma once

#include <stdio.h>
#include <fstream>
#include <Windows.h>
#include <string>
#include <algorithm>

#include<Main.h>
#include<Stack.h>
#include<Queue.h>

class FileLoader
{
	private:

		std::string CartFilePathInput;
		std::string CartFilePathOutput;
		std::string StorageFilePathInput;
		std::string StorageFilePathOutput;

		std::ifstream *CartFileInput;
		std::ofstream *CartFileOutput;
		std::ifstream *StorageFileInput;
		std::ofstream *StorageFileOutput;

		Stack *Cart;
		Queue *Storage;

	public:

		FileLoader(Stack *c, Queue *s) {
			Cart = c;
			Storage = s;
			CartFileInput = nullptr;
			CartFileOutput = nullptr;
			StorageFileInput = nullptr;
			StorageFileOutput = nullptr;
		}

		~FileLoader() {
			if (CartFileInput)
				CartFileInput->close();
			if (CartFileOutput)
				CartFileOutput->close();
			if (StorageFileInput)
				StorageFileInput->close();
			if (StorageFileOutput)
				StorageFileOutput->close();
		}

		void setCartFileInput(std::string input) {
			CartFilePathInput = input;
			CartFileInput = new std::ifstream(input);
			if (!CartFileInput->is_open())
			{
				printf("Cannot open file\n");
				CartFileInput = nullptr;
				return;
			}
		}

		void setCartFileOutput(std::string output) {
			CartFilePathOutput = output;
			CartFileOutput = new std::ofstream(output);
			if (!CartFileOutput->is_open())
			{
				printf("Cannot open file\n");
				CartFileOutput = nullptr;
				return;
			}
		}

		void setStorageFileInput(std::string input) {
			StorageFilePathInput = input;
			StorageFileInput = new std::ifstream(input);
			if (!StorageFileInput->is_open()) {
				printf("Cannot open file\n");
				StorageFileInput = nullptr;
				return;
			}
		}

		void setStorageFileOutput(std::string output) {
			StorageFilePathOutput = output;
			StorageFileOutput = new std::ofstream(output);
			if (!StorageFileOutput->is_open()) {
				printf("Cannot open file\n");
				StorageFileOutput = nullptr;
				return;
			}
		}

		bool readCartFile() {
			if (!CartFileInput) {
				printf("Cannot open cart file");
				return false;
			}
			std::string line;
			while (std::getline(*(CartFileInput), line)) {
				if (line.empty()) {
					continue;
				}
				float price = std::stof(line.substr(line.rfind(" "), line.size()));
				line.erase(line.rfind(" "), line.size());
				int count = std::stoi(line.substr(line.rfind(" "), line.size()));
				line.erase(line.rfind(" "), line.size());
				std::string origin = line.substr(line.rfind(" "), line.size());
				line.erase(line.rfind(" "), line.size());
				std::string name = line;
				if (!price || !count || origin.empty() || name.empty()) {
					printf("Incomplete line in file has occured\n");
					continue;
				}
				std::rotate(origin.begin(), origin.begin()+1, origin.end());
				Item *i = new Item(name, price, count, origin);
				Cart->Push(i);
			}
			return true;
		}

		bool wtiteCartFile() {
			if (!CartFileOutput) {
				printf("Cannot write cart file\n");
				return false;
			}
			CartFileOutput->clear();
			do
			{
				// Name(string) + " " + Origin(string) + " " Count(unsigned int) + " " + Price(float) + "\n"
				std::string line = "";
				Item *i = Cart->Pop();
				line += i->name + " "
					+ i->origin + " "
					+ std::to_string(i->count) + " "
					+ std::to_string(i->price) + "\n";
				(*CartFileOutput) << line;
				if (CartFileOutput->fail()) {
					printf("Error has occured while writing cart file\n");
					return false;
				}
			} while (Cart->Peek() != nullptr);
			return true;
		}
};

