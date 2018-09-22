/* birthday_index.cpp

Copyright 2017-2018 Takeki Sudo and Kazushi Ahara.

This file is part of CubicalRipser_3dim.

CubicalRipser: C++ system for computation of Cubical persistence pairs
Copyright 2017-2018 Takeki Sudo and Kazushi Ahara.
CubicalRipser is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your option)
any later version.

CubicalRipser is deeply depending on 'Ripser', software for Vietoris-Rips 
persitence pairs by Ulrich Bauer, 2015-2016.  We appreciate Ulrich very much.
We rearrange his codes of Ripser and add some new ideas for optimization on it 
and modify it for calculation of a Cubical filtration.

This part of CubicalRiper is a calculator of cubical persistence pairs for 
3 dimensional pixel data. The input data format conforms to that of DIPHA.
 See more descriptions in README.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License along
with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include "birthday_index.h"

using namespace std;

BirthdayIndex2::BirthdayIndex2(){
	birthday = 0;
	index = -1;
	dim = 1;
}

BirthdayIndex2::BirthdayIndex2(double _b, int _i, int _d){
	birthday = _b;
	index = _i;
	dim = _d;
}

BirthdayIndex2::BirthdayIndex2(const BirthdayIndex2& b){
	birthday = b.birthday;
	index = b.index;
	dim = b.dim;
}

void BirthdayIndex2::copyBirthdayIndex2(BirthdayIndex2 v){
	birthday = v.birthday;
	index = v.index;
	dim = v.dim;
}

double BirthdayIndex2::getBirthday2(){
	return birthday;
}

long BirthdayIndex2::getIndex2(){
	return index;
}

int BirthdayIndex2::getDimension2(){
	return dim;
}

void BirthdayIndex2::print2(){
	std::cout << "(dob:" << birthday << "," << index << ")" << std::endl;
}

void BirthdayIndex2::VertexPrint2(){
	int px = index & 0x01ff;
	int py = (index >> 9) & 0x01ff;
	int pz = (index >> 18) & 0x01ff;
	int pm = (index >> 27) & 0xff;
	
	cout << "birthday : (m, z, y, x) = " << birthday << " : (" << pm << ", " << pz << ", " << py << ", " << px << ")" << endl; 
}
	
bool BirthdayIndexComparator2::operator()(const BirthdayIndex2& o1, const BirthdayIndex2& o2) const{
	if(o1.birthday == o2.birthday){
		if(o1.index < o2.index){
			return true;
		} else {
			return false;
		}
	} else {
		if(o1.birthday > o2.birthday){
			return true;
		} else {
			return false;
		}
	}
}

 	
bool BirthdayIndexInverseComparator2::operator()(const BirthdayIndex2& o1, const BirthdayIndex2& o2) const{
	if(o1.birthday == o2.birthday){
		if(o1.index < o2.index){
			return false;
		} else {
			return true;
		}
	} else {
		if(o1.birthday > o2.birthday){
			return false;
		} else {
			return true;
		}
	}
}
	