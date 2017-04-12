using namespace std;

class Processor
{
	public:
		Processor();
		~Processor();
		
		bool setInputFile(string name);
		void scanFile();
		void refreshStacks();

		string fileName;
		int stackSize;
};
