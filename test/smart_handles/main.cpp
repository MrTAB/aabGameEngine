

#include"../../utility/smart_ptr.hpp"
#include<list>

template <class T_Class>
class Handled
{
	protected:

	class Deleter;
	friend class Deleter;
	class Deleter
	{
		public:

		void operator () (T_Class *t)
		{
			delete t;
		}
	};

	class NullDeleter
	{
		public:

		void operator () (T_Class *)
		{
			// nothing //
		}
	};


	public:

	virtual ~Handled ()
	{
	}
};


class MakeSceneNode : public Handled <MakeSceneNode>
{
public:

	typedef aab::Smart<MakeSceneNode>::Ptr Ptr;

private:

	typedef std::list <Ptr> list;

	list children;

protected:

	explicit MakeSceneNode ()
	{
	}

	virtual ~MakeSceneNode () throw ()
	{
	}

	friend class Handled <MakeSceneNode>::Deleter;


public:

    static Ptr null ()
    {
        Ptr px((MakeSceneNode*)NULL, NullDeleter());
        return px;
    }

    static Ptr create()
    {
        Ptr px(new MakeSceneNode(), Deleter());
        return px;
    }



};

typedef MakeSceneNode::Ptr MyClass;
typedef MakeSceneNode SceneNode;


class SubClass : public SceneNode
{
	private:

	protected:

	explicit SubClass ()
	{
	}

	virtual ~SubClass () throw ()
	{
	}

	public:

	typedef aab::Smart<SubClass>::Ptr Ptr;

    static Ptr create()
    {
        Ptr px(new SubClass(), Deleter());
        return px;
    }

    friend Ptr createSubClass();
};

typedef SubClass::Ptr MySub;

MySub createSubClass()
{
	MySub px(new SubClass(), SubClass::Deleter());
	return px;
}

int main ()
{
	MyClass c = SceneNode::create ();

	MyClass null = SceneNode::null ();

	MySub sub = createSubClass ();

	//delete sub.get ();

	return 0;
}


