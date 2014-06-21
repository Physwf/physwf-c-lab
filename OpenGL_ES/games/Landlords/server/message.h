#include <serialization.h>
#include "game.h"

class MsgBase 
{
	public:
		MsgBase();
		MsgBase(unsigned short mid);
		~MsgBase();
	public:
		virtual void writeExternal(Bytes* output);
		virtual void readExternal(Bytes* input);
	protected:
		virtual void writeBody(Bytes* output) = 0;
		virtual void readBody(Bytes* input) = 0;
	private:
		void writeHead(Bytes* output, Bytes* body);
		void readHead(Bytes *input);
		
	public:
		static const short int HEAD_LENGTH = 18;
		static unsigned int UID;
		unsigned short msgid;
		unsigned int userid;
	private:
		unsigned int length;
};

enum
{
	MSG_BRDCST_DEAL_RESULT_999=999,
	MSG_SRV_WAIT_LOOT_1000=1000,
	MSG_CLNT_LOOT_SCORE_1001
};

class MSG_BRDCST_DEAL_RESULT:public MsgBase
{
	public:
		MSG_BRDCST_DEAL_RESULT();
		~MSG_BRDCST_DEAL_RESULT();
	protected:
		void writeBody(Bytes* output);
		void readBody(Bytes* input);
	public:
		PDealResult result;
};

class MSG_SEV_WAIT_LOOT:public MsgBase
{
	public:
		MSG_SEV_WAIT_LOOT();
		~MSG_SEV_WAIT_LOOT();
	protected:
		void writeBody(Bytes* output);
		void readBody(Bytes* input);
};

class MSG_CLNT_LOOT_SCORE:public MsgBase
{
	public:
		MSG_CLNT_LOOT_SCORE(int mid);
		~MSG_CLNT_LOOT_SCORE();
	protected:
		void writeBody(Bytes* output);
		void readBody(Bytes* input);	
};

