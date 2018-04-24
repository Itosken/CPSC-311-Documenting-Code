//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<fstream>
#include	<iostream>
#include	<string>
#include <map>

#include	"Catalog.h"

using namespace std;

bool	Catalog::AddCategory(uint64_t categoryNumber, const string& name)
{
	// to be completed
	//Given a category number and name, add it to the catalog. It will have an empty product list.
	//Return false if the category number already exists in the catalog, true otherwise.
	cateMapIt it;
	for(it = cate.begin(); it!= cate.end();it++){
		if(it->first == categoryNumber){
			return false;
		}
	}
	cate.insert(cateMapValue(categoryNumber,name));
	cateCounter++;

	return true;
	
}

bool	Catalog::AddProduct(uint64_t categoryNumber, uint64_t productNumber, const string& name)
{
	// to be completed
	//Given a category number, a product number, and a product name, add the product to the catalog.
	//Return false if the category number doesn’t exist in the catalog or if the product number
	//already exists within the category, true otherwise.
	cateMapIt it;
	for(it = cate.begin();it != cate.end();it++){
		if(it->first == categoryNumber){
			for(prodMapIt it2 = prod.begin();it2 != prod.end();++it2){
				if(it2->second.prodName == name){
					return false;
				}
			}
			Products pro;
			pro.categoryN = categoryNumber;
			pro.prodName = name;
			pro.productNum = productNumber;
		//	cout <<"\nProduct Category:" << pro.categoryN << " ProductNumber: "<< pro.productNum << " Product Name:"<< pro.prodName << endl;
			prod.insert(prodMapValue(productNumber,pro));

		}
	}
	return false;
}



uint64_t	Catalog::GetCategoryCount()
{
	// to be completed
	//Return the number of categories in the catalog.
	return cateCounter;
}

int64_t	Catalog::GetProductCount(uint64_t categoryNumber)
{
	// to be completed
	// Given a category number, return the number of products in the category;
	//return -1 if the category doesn’t exist.
	prodMapIt it;
	int count = 0;
	for(it = prod.begin(); it != prod.end();++it){
		if(it->second.categoryN == categoryNumber){
			count++;
		}
	}
	return count;
}

bool	Catalog::Load(const string& fileName)
{
	// to be completed
	//Load the catalog from a file, given the file’s name. Return false if the catalog can’t
	//be loaded, either because the file doesn’t exist or isn’t in the correct format.
	ifstream iFile;
	string file;
	string info[4];
	int category;
	iFile.open(fileName);

	if (!iFile) {
		cerr << "Error in Opening File.\n";
		return false;
	}
	while(iFile){
		getline(iFile,file, '\n');
		istringstream iss(file);
		for(int i  = 0; i < 3; i++){
			getline(iss,info[i],'\t');
		}
		if(info[0] == "Category"){
			int x = 0;
//			cout << "Test: " << info[1] << " " << info[2] << endl;
			stringstream convert2(info[1]);
			convert2 >> x;
			category = x;
			AddCategory((unsigned)x,info[2]);
		}
		else{
//			cout << "Test: " << info[0] << " " << info[1] << endl;
			stringstream convert(info[0]);
			int x = 0;
			convert >> x;
//			cout << "Test: " << category << " " << x << endl;
			AddProduct(category,x,info[1]);
		}
	}
//	for(int i  = 0; i < 3; i++){
//		cout << info[i] << endl;
//	}
//	cout << file << endl;
//	getline(iFile,file, '\n');

//	cout << file << endl;

	return true;
}

//****************************************************************************************
//
//	Show... methods
//
//	The stream argument allows thess functions to write its output to any output stream,
//	such as cout or a file, that the caller passes. The argument's name "stream" should
//	be used just as you would use "cout":
//
//		stream << "X = " << x << endl;
//
//	The output will go where the caller intended without special action by this function.
//
//****************************************************************************************

bool	Catalog::ShowProduct(ostream& stream, uint64_t categoryNumber, uint64_t productNumber)
{
	// to be completed
	//Given a category number and a product number, show the product number and name separated by a tab.
	//Return false if the category number doesn’t exist in the catalog or if the product number doesn’t
	//exist within the category.
	prodMapIt it;
	cateMapIt it2;
	bool exist = false;
	for(it2 = cate.begin();it2 != cate.end();it2++){
		if((unsigned)it2->first == categoryNumber){
			exist = true;
		}
	}
	if(!exist){
		return false;
	}
	for(it = prod.begin();it != prod.end();++it){
		if(it->second.categoryN == categoryNumber){
			if(it->second.productNum == productNumber){
				stream << productNumber << "\t" << it->second.prodName;
				return true;
			}
		}
	}
	return false;
}

bool	Catalog::ShowCategory(ostream& stream, uint64_t categoryNumber)
{
	// to be completed
	//Given a category number, show only its products in order by product number. Return false
	//if the category number doesn’t exist in the catalog. Use the same format as the text file in Load.
	prodMapIt it;
	cateMapIt it2;
	bool exist = false;
	for(it2 = cate.begin();it2 != cate.end();it2++){
		if((unsigned)it2->first == categoryNumber){
			exist = true;
			stream << "Category\t" << categoryNumber << "\t"<< it2->second << endl;
			for(it = prod.begin();it != prod.end();++it){
				if(it->second.categoryN == categoryNumber){
					stream << it->second.productNum << "\t" << it->second.prodName << endl;
				}
			}
			return true;
		}
	}
	if(!exist){
		return false;
	}
	return true;
}

bool	Catalog::ShowAll(ostream& stream)
{
	// to be completed
	//Show the entire catalog, category by category, in order by category number. Under each category,
	//show its products in order by product number. Use the same format as the text file in Load.
	prodMapIt it;
	cateMapIt it2;
	if(prod.empty()){
		return false;
	}
	for(it2 = cate.begin();it2 != cate.end();it2++){
		int num = it2->first;
		stream << "Category\t" << it2->first << "\t"<< it2->second << endl;
		for(it = prod.begin();it != prod.end();++it){
		if(num == it->second.categoryN){
			stream << it->second.productNum << "\t" << it->second.prodName << endl;
		}
		}


	}
	return true;
}

