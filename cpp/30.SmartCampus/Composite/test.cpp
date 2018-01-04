#include <iostream>
#include "Composite.h"

namespace GoFExample
{
using namespace std;
using namespace GoFPatterns;

class ElectronicComponent
{
public:
	virtual void PrintSpec(ostream& ostr, string prefix = "")= 0;
	virtual void DoFunction(float& voltage, float& current) = 0;
};

class Resistor:public ElectronicComponent
{
	float resistance_Ohm;
	Resistor(){}
public:
	Resistor(float ohm)
	:resistance_Ohm(ohm)
	{        
    }

	void PrintSpec(ostream& ostr, string prefix = "")
	{
		ostr<<prefix<<"Resistor ("<< resistance_Ohm <<" Ohm )"<<endl;
	}

	void DoFunction(float& voltage, float& current)
	{
		cout<<endl<<"Resistor Input ("<<voltage<<" V ,"<<current<<" Amp) Resistance = "<< resistance_Ohm <<endl;
	}
};

class Capacitor:public ElectronicComponent
{
	float capacitance_muF; //Capacitance value in micro fared.
	Capacitor(){}
public:
	Capacitor(float muF)
	:capacitance_muF(muF)
	{

	}

	void PrintSpec(ostream& ostr, string prefix = "")
	{
		ostr<<prefix<<"Capacitor ("<< capacitance_muF <<" muF )"<<endl;
	}

	void DoFunction(float& voltage, float& current)
	{
		cout<<endl<<"Capacitor Input ("<<voltage<<" V ,"<<current<<" Amp) Capacitance ="<< capacitance_muF<<endl;
	}
};

class ICChip:public Composite<ElectronicComponent>
{
public:
	void PrintSpec(ostream& ostr, string prefix = "")
	{
		ostr<<prefix<<"ICChip With "<< children.size()<< 
						" Components " <<endl;
		for( unsigned int i = 0; i < children.size(); i++)
		{
			ostr<<prefix;
			children[i]->PrintSpec(ostr,"\t");
		}
	}
	void DoFunction(float& voltage, float& current)
	{
		cout<<endl<<"ICChip Input ("<<voltage<<" V ,"<<current<<" Amp)";
		for( unsigned int i = 0; i < children.size(); i++)
		{
			children[i]->DoFunction(voltage,current);
		}
	}
};
/*
 * ICChip is a COMPOSITE class which consist of many ElectronicComponents -
 * such as Resistors, Capacitors or ICChips.
 * So it can be said a Composite of ElectronicComponents. Thus it is inherited from -
 * Composite<ElectronicComponent>. This makes it a container class of -
 * other ElectronicComponents and at the same time it, it by itself -
 * an ElectronicComponent.
 */
class PCB:public Composite<ElectronicComponent>
{
public:
	/*
	 * PrintSpec of PCB prints no only the spec of the PCB itself
	 * but also the Spec of its Child components in a TAB ("\t") intended format.
	 */
	void PrintSpec(ostream& ostr, string prefix = "")
	{
		ostr<<prefix<<"PCB With "<< children.size()<< " Components " <<endl;
		for( unsigned int i = 0; i < children.size(); i++)
		{
			ostr<<prefix;
			children[i]->PrintSpec(ostr,"\t");
		}
	}
	/*
	 * Real functioning of PCB is achieved by sending its input Voltage & Current
	 * To the sub components inside it.
	 * So the DoFunction - of PCB send its input Voltage & Current to all the
	 * child components inside it.
	 */
	void DoFunction(float& voltage, float& current)
	{
		cout<<endl<<"PCB Input ("<<voltage<<" V ,"<<current<<" Amp) ";
		for( unsigned int i = 0; i < children.size(); i++)
		{
			children[i]->DoFunction(voltage,current);
		}
	}
};
}//end name space GoFExample

using namespace GoFExample;
/*
 * Program entry point; main() function
 */
int main()
{
	Resistor r1(50), r2(70); //Define Resistors
	Capacitor c1(200),c2(300); //Define Capacitors

	ICChip ic1; //Create a Chip
	ic1.AddChild(new Resistor(2000)); // Add a Resistor inside the ICChip
	ic1.AddChild(new Capacitor(1000)); // Add a Capacitor inside the ICChip

	PCB pcb1; //Make  PCB Object and add the Resistor, Capacitors and ICChip on it
	pcb1.AddChild(&r1);
	pcb1.AddChild(&c1);
	pcb1.AddChild(&c2);
	pcb1.AddChild(&ic1);
	pcb1.AddChild(&ic1); // Duplicate child entries are ignored.

	cout<<"\n=========== Printing the PCB Spec =========="<<endl;
	pcb1.PrintSpec(cout);
	float v =110, i = 5;
	cout<<"\n=========== DoFunction(110,5) of PCB =========="<<endl;
	pcb1.DoFunction(v,i);
	cout<<"\n=========== Removing c2 from PCB =========="<<endl;
	pcb1.RemoveChild(&c2);
	cout<<"\n=========== Printing the PCB Spec =========="<<endl;
	pcb1.PrintSpec(cout);
	
	return 0;
}






