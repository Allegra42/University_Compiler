

class Buffer {
	public:
		Buffer();
		~Buffer();
		char nextChar();
		void resetBy(int step);
		void init();
		int main();
	
	private:
		char* text;
};
