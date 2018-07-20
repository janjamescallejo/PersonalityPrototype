// PersonalityPrototype.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include "Database.h"

using namespace std;

double sout;
database d;
string J48Descision(int i,double Openness, double Conscientiousness, double Extraversion, double Agreeableness, double Neuroticism)
{
	string decision;
	if (Conscientiousness <= 48)
	{
		decision = "Low";
	}
	else
	{
		decision = "High";
	}
	d.insertJ48Result(i, decision);
	return decision;
}
string SVMDescision(int i,double Openness, double Conscientiousness, double Extraversion, double Agreeableness, double Neuroticism)
{
	double bias = 0.7751;
	double Oweight = 0.2576;
	double Cweight = -1.1008;
	double Eweight = 0.4318;
	double Aweight = -1.3461;
	double Nweight = 0.4136;
	double judgment = bias + Openness * Oweight + Conscientiousness * Cweight + Extraversion * Eweight + Agreeableness * Aweight + Neuroticism * Nweight;
	sout = judgment;
	if (judgment < 0)
	{
		d.insertSVMResult(i, judgment, "Low");
		return "Low";
	}
	else
	{
		d.insertSVMResult(i, judgment, "High");
		return "High";
	}
}
void NNDescision(int i,double Openness, double Conscientiousness, double Extraversion, double Agreeableness, double Neuroticism)
{
	double Node0[4];
	Node0[0] = 1.9681233815607992;
	Node0[1] = 4.315149971626586;
	Node0[2] = -5.032923755158269;
	Node0[3] = -4.664559352707409;
	double Node1[4];
	Node1[0] = -1.966869397528337;
	Node1[1] = -4.313565467074465;
	Node1[2] = 5.031059656617999;
	Node1[3] = 4.661951293969117;
	double Node2[6];
	Node2[0] = 1.3922360715291697;
	Node2[1] = -1.000001369357454;
	Node2[2] = 2.5527963941780687;
	Node2[3] = -2.118330523880014;
	Node2[4] = 6.016086257658944;
	Node2[5] = -3.949191343543312;
	double Node3[6];
	Node3[0] = -1.6918899122722437;
	Node3[1] = 6.713892265683045;
	Node3[2] = -2.456757936004637;
	Node3[3] = 0.05456128345924017;
	Node3[4] = -2.144708005850931;
	Node3[5] = 1.6687936147836986;
	double Node4[6];
	Node4[0] = 3.0570941539538166;
	Node4[1] = 1.8197194025925858;
	Node4[2] = 1.672730545255241;
	Node4[3] = 2.1410640197503836;
	Node4[4] = -2.4776393870365294;
	Node4[5] = -2.2411315272793932;

	double firstcom[3];
	firstcom[0] = Node2[0] + Node2[1] * Openness + Node2[2] * Conscientiousness + Node2[3] * Extraversion + Node2[4] * Agreeableness + Node2[5] * Neuroticism; 
	firstcom[1] = Node3[0] + Node3[1] * Openness + Node3[2] * Conscientiousness + Node3[3] * Extraversion + Node3[4] * Agreeableness + Node3[5] * Neuroticism; 
	firstcom[2] = Node4[0] + Node4[1] * Openness + Node4[2] * Conscientiousness + Node4[3] * Extraversion + Node4[4] * Agreeableness + Node4[5] * Neuroticism;
	string decision;
	double secondcomp[3];
	for (int i = 0; i < 3; i++)
	{
		secondcomp[i] = tanh(firstcom[i]);
	}
	double highcalc1 = Node0[0] + Node0[1] * secondcomp[0] + Node0[2] * secondcomp[1] + Node0[3] * secondcomp[2]; 
	double highcalc2 = tanh(highcalc1);
	double lowcalc1 = Node1[0] + Node1[1] * secondcomp[0] + Node1[2] * secondcomp[1] + Node1[3] * secondcomp[2];
	double lowcalc2 = tanh(lowcalc1);
	if (highcalc2 > lowcalc2)
	{
		decision = "High";
	}
	else
	{
		decision = "Low";
	}
	d.insertNNResult(i, highcalc2, lowcalc2, decision);
	cout << "High: " << highcalc2 << "  Low " << lowcalc2 << endl;
}

int main()
{
	int i=1;
	string in;
	double Openness;
	double Conscientiousness;
	double Extraversion;
	double Agreeableness;
	double Neuroticism;
	cout << "Personality Prototype" << endl;
	cout << "Please take a Personality Test at PersonalityTest.org.uk and record the result" << endl;
	ifstream sample("C:\\Users\\Lenovo\\Desktop\\Thesis\\Data Sets\\Personality Test Dataset.csv");
	if (!sample.is_open())
		cout << "Error: File Open" << '\n';
	try {
		while (sample.good())
		{

			getline(sample, in, ',');
			Openness = stod(in); in = "";
			getline(sample, in, ',');
			Conscientiousness = stod(in); in = "";
			getline(sample, in, ',');
			Extraversion = stod(in); in = "";
			getline(sample, in, ',');
			Agreeableness = stod(in); in = "";
			getline(sample, in, '\n');
			Neuroticism = stod(in); in = "";
			
			string dec = SVMDescision(i,Openness, Conscientiousness,Extraversion,Agreeableness,Neuroticism);
			string dec1 = J48Descision(i,Openness, Conscientiousness, Extraversion, Agreeableness, Neuroticism);

			cout <<i<<". SVM: " << dec << " Value: " << sout << " J48: " << dec1 << " Neural: ";
			NNDescision(i,Openness, Conscientiousness, Extraversion, Agreeableness, Neuroticism);
			i++;

		}
	}
	catch (exception e) {
		sample.close();
	}
	sample.close();
	d.databaseclose();
	system("PAUSE");
    return 0;
}

