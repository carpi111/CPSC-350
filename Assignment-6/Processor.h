using namespace std;

class Processor
{
    private:
        string fileName;
        int numElements;

        double *quickSortArray;
        double *insertSortArray;
        double *gnomeSortArray;

	public:
		Processor();
		~Processor();

		bool setInputFile(string name);
		void scanFile();

        void quickSort(double array[], int left, int right);
        int partition(double array[], int left, int right);

        void insertionSort(double array[]);

        void gnomeSort(double array[]);

        void sortAll();
        bool isSorted(double array[]);
        void swap(double array[], int a, int b);

        string getFileName();
};
