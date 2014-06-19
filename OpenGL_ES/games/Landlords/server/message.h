class MsgBase 
{
	public:
		MsgBase(unsigned int mid);
		~MsgBase();
	public:
		void writeExternal(char* output);
		void readExternal(char* input);
	protected:
		void writeBody(char* output);
		void readBody(char* input);
	private:
		void writeHead(char* output, char* body);
		void readHead(char *input);
		
	public:
		static const short int HEAD_LENGTH = 18;
		static unsigned int UID;
		unsigned int msgid;
		unsigned int userid;
	private:
		unsigned int length;
}