#ifndef __SCENEBASE__
#define __SCENEBASE__


class SceneBase {
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;
	~SceneBase()  {};
private:

};

#endif // !__SCENEBASE__
