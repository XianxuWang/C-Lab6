/*
 * hashNode.cpp
 *
 *  Created on: 2019年11月21日
 *      Author: leoyin
 */

#include "hashNode.hpp"
#include <stdlib.h>

hashNode::hashNode(){
	keyword="";
	valuesSize=0;
	currSize=0;
	values=NULL;
}

hashNode::hashNode(string s){
	keyword=s;
	valuesSize=10;
	currSize=0;
	values=new string[valuesSize];
}

hashNode::hashNode(string s, string v){
	keyword=s;
	valuesSize=10;
	currSize=1;
	values=new string[valuesSize];
	values[0]=v;
}

void hashNode::dblArray(){
	string x[valuesSize];
	for(int i=0;i<valuesSize;i++){
		x[i]=values[i];
	}
	delete []values;
	values=new string[2*valuesSize];
	for(int i=0;i<valuesSize;i++){
		values[i]=x[i];
	}
	valuesSize*=2;
}

void hashNode::addValue(string v){
	currSize++;
	if(currSize>valuesSize){
		dblArray();
	}
	values[currSize-1]=v;
}

string hashNode::getRandValue(){
	string x;
	if(currSize==0){
		x="";
	}
	else{
		int idx=rand()%currSize;
		x=values[idx];
	}
	return x;
}
