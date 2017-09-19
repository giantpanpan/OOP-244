#ifndef RACING_ENGINE_H
#define RACING_ENGINE_H
 
namespace racing {
	class Engine {
		char* m_pModel; //a pointer which stores a string
		short m_hp;
	public:
		void setEmpty(); 
		void set(const  char* pModel, short hp);
		void display() const; //queries, don't change data attributes
	};
};

#endif
