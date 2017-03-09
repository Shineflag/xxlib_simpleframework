/*

MP �������뺬��������Щ����

typedef xx::MemPool<
.............
SceneBase,
SceneObjBase,
FSMBase,
xx::List<FSMBase*>, 
xx::List<SceneObjBase*, true> 
................> MP;

*/

// �� Update �麯������Ļ���
struct UpdateBase : xx::MPObject
{
	// ���ط� 0 ��ʾ��ɱ. ����ͨ����������������, ����ͨ����ʾ����
	virtual int Update() = 0;
};

struct SceneBase;
struct SceneObjBase;

// ״̬������. ֻ���� SceneObjBase �ĺ���������. ������ֱ�� Release. ��ɱ���� PopFSM �� Update ���ط� 0
struct FSMBase : UpdateBase
{
	SceneObjBase* owner;
	FSMBase(SceneObjBase* owner) : owner(owner) {}
};

// �������ӵĻ���( �������� ). ֻ���� SceneBase �ĺ���������.
struct SceneObjBase : UpdateBase
{
	// ָ�򳡾�����
	SceneBase* sceneBase;

	// λ�ڳ����������е��±�( for ����ʽ��ɾ )
	uint32_t sceneObjsIndex;

	// todo: �ṩһ�������������ϸ� FSM ��ִ�н��( ��������, �����˳�����, ����¼�����֮�� )
	xx::List<FSMBase*>* fsmStack;
	FSMBase* currFSM = nullptr;
	FSMBase* deadFSM = nullptr;		// �ӳ�ɱ��

	SceneObjBase(SceneBase* sceneBase);
	~SceneObjBase();

	template<typename T, typename ...Args>
	T* CreateFSM(Args&&...args);
	void SetFSM(FSMBase* fsm);
	void PushFSM(FSMBase* fsm);
	void PopFSM();
	virtual int Update() override;
};

// ��������( �������ڴ��, ��������, LUA State )
struct SceneBase : xx::MPObject
{
};