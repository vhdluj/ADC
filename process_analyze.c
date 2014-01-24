#include <iostream>
#include <TFile.h>
#include <string>


int process_analyze(const char* filename,const char* config_file ,int evtNum)
{
        /*  We get the value of mV form file name (e.g. thLVL1234.hld.root cut thLVL and cut .hld.root)*/
	std::string milivolts = std::string(filename);
	milivolts.erase(milivolts.length()-9,9);
	std::cout<<milivolts<<std::endl;
        milivolts.erase(0,27);
	std::cout<<milivolts<<std::endl;
	/**/

        TFile* _file0 = TFile::Open(filename);
        T->Process("analyze_trb3.C");	

	ofstream outFile;
	outFile.open("/home/vhdluj/TRB3/Unpacker/tools2/output/ACvalues.txt", std::ofstream::app);
	outFile<<milivolts<<"\t"<<timeDiffAC->GetMean()<<endl;
	outFile.close();

	ofstream outFile1;
	outFile1.open("/home/vhdluj/TRB3/Unpacker/tools2/output/AC_RMSvalues.txt", std::ofstream::app);
	outFile1<<milivolts<<"\t"<<timeDiffAC->GetRMS()<<endl;
	outFile1.close();

	ofstream outFile2;
	outFile2.open("/home/vhdluj/TRB3/Unpacker/tools2/output/BDvalues.txt", std::ofstream::app);
	outFile2<<milivolts<<"\t"<<timeDiffBD->GetMean()<<endl;
	outFile2.close();

	ofstream outFile3;
	outFile3.open("/home/vhdluj/TRB3/Unpacker/tools2/output/BD_RMSvalues.txt", std::ofstream::app);
	outFile3<<milivolts<<"\t"<<timeDiffBD->GetRMS()<<endl;
	outFile3.close();



}
