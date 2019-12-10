/*
 * hashMap.cpp
 *
 *  Created on: 2019年11月21日
 *      Author: Yisi Yin, Xianxu Wang, Yifan Yang
 *
 */
#include "hashMap.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;


hashMap::hashMap(bool hash1,bool coll1){
	h1=hash1;
	c1=coll1;
	numKeys=0;
	mapSize=251;
	collisionct1=0;
	collisionct2=0;
	first="";
	map=new hashNode *[mapSize];
	for(int i=0;i<mapSize;i++){
		map[i]=NULL;
	}
}

int hashMap::calcHash(string k){
	int x=0;
	int len=k.size();
	for(int i=0;i<len;i++){
		x+=k[i];
	}
	return (k[0]*x)%mapSize;
}

int hashMap::calcHash2(string k){
	int len=k.size()*k.size();
	int vCount=0;
	int cCount=0;
	for(int i=0;i<k.size();i++){
		if(k[i]=='A'||k[i]=='a'||k[i]=='e'||k[i]=='E'||k[i]=='i'||k[i]=='I'||k[i]=='o'||k[i]=='u'||k[i]=='O'||k[i]=='u'||k[i]=='y'||k[i]=='Y'){
			vCount++;
		}
		else{
			cCount++;
		}
	}
	len=len*cCount*vCount;
	len=len-cCount+vCount;
	return len%mapSize;
}

void hashMap::getClosestPrime(){
	int x=2*mapSize;
	bool y=false;
	for(int i=2;i<(int)sqrt(x);i++){
		if(x%i==0){
			y=true;
		}
	}
	while(y){
		x++;
		y=false;
		for(int i=2;i<(int)sqrt(x);i++){
				if(x%i==0){
					y=true;
				}
		}
	}
	mapSize=x;
}


int hashMap::collHash1(int h, int i){
	return ((h+i*i*i)%mapSize);
}

int hashMap::findKey(string k){
	int x=calcHash(k);
	int y=x;
	if(map[x]->keyword==k){
		return x;
	}
	else{
		int i=1;
		while(map[x]->keyword!=k||i<collisionct2+1){
			x=collHash1(y,i);
			i++;
		}
		if(map[x]->keyword!=k){
			x=-1;
		}
	}
	return x;
}

void hashMap::reHash(){
	hashNode *x[numKeys];
	int j=0;
	int keyIdx;
	int coll=1;
	for(int i =0;i<mapSize;i++){
		if(map[i]!=NULL){
			x[j]=map[i];
			j++;
		}
	}
	getClosestPrime();
	delete []map;
	map=new hashNode *[mapSize];
	for(int i=0;i<mapSize;i++){
		map[i]=NULL;
	}
	for(int y=0;y<numKeys;y++){
		keyIdx=calcHash(x[y]->keyword);
		if(map[keyIdx]==NULL){
			map[keyIdx]=x[y];
		}
		else{
			collisionct1++;
			keyIdx=collHash1(keyIdx,coll);
			coll++;
			while(map[keyIdx]!=NULL){
				collisionct2++;
				keyIdx=collHash1(keyIdx,coll);
				coll++;
			}
			map[keyIdx]=x[y];
			coll=1;
		}
	}
}

int hashMap::getIndex(string k){
	if(((double)numKeys)/((double)mapSize)>.7){
		cout<<"rehash"<<endl;
		reHash();
	}
	int x=calcHash(k);
	int coll=1;
	int y=x;
	bool loop=map[x]!=NULL;
	while(loop){
		if(map[x]==NULL){
			loop=false;
		}
		else if(map[x]->keyword==k){
			loop=false;
		}
		else{
			if(coll==1){collisionct1++;}
			else{collisionct2++;}
			x=collHash1(y,coll);
			coll++;
		}
	}
	return x;
}

void hashMap::addKeyValue(string k, string v){
	int x=getIndex(k);
	if(map[x]==NULL){
		map[x]=new hashNode(k,v);
		numKeys++;
	}
	else{
		map[x]->addValue(v);
	}
}
void hashMap::printMap() {
    for (int i=0; i<mapSize; i++){
        cout << i << " ";
        if (map[i]==NULL){
            cout << "";
        } else{

            for (int j=0; j<map[i]->currSize; j++){
                cout << map[i]->values[j]<< ", ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
