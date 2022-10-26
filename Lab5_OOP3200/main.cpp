/*
* Name: - Nirmal Patel & Megh Patel
* Studentid: - 100830820, 100802838
* Date: - 24/10/2022
* Subject: - OOPs 3200
* 
*/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>


#include "Vector2D.h"

template<typename T>
void NewMap(const std::string& file_name)
{
	std::ifstream Vector2DInStream(file_name, std::ios::in);
	if (!Vector2DInStream) {
	
		throw std::runtime_error(file_name + " Could not be opened for input. Check that the file exists.");
	}
	else
	{
		try {
			std::string str;

		
			int point_count = 0;

			
			std::map<std::string, Vector2D<float>*> vectorAtlas;
			if (Vector2DInStream >> str)
			{
				int i = 0;
				std::string nir = str;
				std::string st[100];	
				char character;
				while (Vector2DInStream >> std::noskipws >> character)
				{
					if (character >= 65 && character <= 90)
					{
						nir += character;
					}
					else if (character == 32 && nir != "")
					{
						st[i] = nir;
						i++;
						nir = "";
					}
				}
				Vector2DInStream.close();

				std::ifstream Vector2DInStream1(file_name, std::ios::in);
				auto* temp_point = new Vector2D<T>();
				i = 0;
				while (Vector2DInStream1 >> *temp_point)
				{
					vectorAtlas[st[i]] = new Vector2D<float>(temp_point->GetX(), temp_point->GetY());
					i++;				
					point_count++;
				}

				std::map<std::string, Vector2D<float>*>::iterator itr;
				std::map<std::string, Vector2D<float>*>::iterator itr2;

				double dis_tot = 0.0;
				double distance = 0.0;
				
				
				for (itr = vectorAtlas.begin(), itr2 = itr++; itr != vectorAtlas.end(); ++itr, ++itr2)
				{
					distance = itr->second->Distance(*itr->second, *itr2->second);
					dis_tot += distance;
				}
				
				
				std::string point_name = "";
				std::cout << "The Map contains " << point_count << " points for a total distance of " << dis_tot << std::endl;

				
				bool run = true;
				
				
				while (run)
				{
					std::cout << "\nEnter the Label you wish to go to (\"quit\" to end): ";
					std::cin >> point_name;
					itr = vectorAtlas.begin();
					itr2 = itr;
					distance = 0.0;
					bool point_exists = false;
					
					for (int i = 0; i < point_count; i++)
					{

						if (!point_name.compare(itr2->first))
						{
							distance = itr->second->Distance(*itr->second, *itr2->second);
							std::cout << "Distance Between " << itr->first << *itr->second << " and " << itr2->first << *itr2->second << "  is " << distance << std::endl;
							point_exists = true;
							break;
						}
						if (point_name == "quit")
						{
							run = false;
							break;
						}
						itr2++;
					}
					if (!point_exists && point_name != "quit")
					{
						std::cout << "There is not point labelled \"" << point_name << "\" in the map." << std::endl;
					}
				}
				Vector2DInStream.close();
			}
			else
			{
				throw std::exception("The Map is Empty. Check that the file contains valid data in the correct format.");
			}
		}
		catch (...)
		{
			std::cout << "An Error occured at run time\n";
		}
	}


}

int main()
{

	std::string wrong_file_name = "p.txt";
	std::string empty_file = "empty.txt";
	std::string file_name = "PointData.dat";


	bool run = true;
	while (run)
	{
		try
		{
		
			char choice = '0';
			std::cout << "\nPlease select from following:\n"
				<< "1: To check file exist or not\n"
				<< "2: To check file is empty or not\n"
				<< "3: To run the program\n"
				<< "4: To quit the program\n"
				<< "\nEnter choice: ";

			std::cin >> choice;
			switch (choice)
			{
			case '1':
				
				NewMap<float>(wrong_file_name);
				break;
			case '2':
				
				NewMap<float>(empty_file);
				break;
			case '3':
				
				NewMap<float>(file_name);
				break;
			case '4':
			
				run = false;
				std::cout << "Quit program..";
				break;
			default:
			
				std::cout << "\nInvalid Input! Check options for input value!! (MUST BE 1 or 2 or 3 or 4)\n";
			}
		}
		catch (std::exception& ex)
		{
			
			std::cout << ex.what() << std::endl;
		}
	}

	


	std::cout << std::endl << std::endl;
	return 0;
}
