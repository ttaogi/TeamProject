#pragma once

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;		//리소스 아이디
		HDC			hMemDC;		//메모리 DC
		HBITMAP		hBit;		//비트맵 가져올
		HBITMAP		hOBit;		//올드 비트맵
		float		x;
		float		y;
		int			width;		//이미지 가로크기
		int			height;		//이미지 세로크기
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			maxFrameIdx;
		int			frameWidth;
		int			frameHeight;
		BYTE		LoadType;	//로드맵 타입

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX =0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			maxFrameIdx = 0;
			frameWidth = 0;
			frameHeight = 0;
			LoadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO; // 포인터는 사용하기전에 if문으로 한번더 물어봐라 삭제하든 이용하든

private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;
	BOOL			_isTrans;		
	COLORREF		_transColor;	//배경색을 없앨 RGB값 (32비트 정수형), RGB(각각 1바이트 0~255 농도 표현 가능)

	BLENDFUNCTION	_blendFunc;		//블랜드 함수
	LPIMAGE_INFO	_blendImage;	//블랜드 이미지

public:
	//빈 비트맵 초기화
	HRESULT init(int width, int height);

	//이미지 리소스 초기화
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	//이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY, int maxFrameIdx,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width,
		int height, int maxFrameX, int maxFrameY, int maxFrameIdx,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//알파 블랜드 초기화
	HRESULT initForAlphaBlend(void); //무한이 이미지 클래스에서 번진다
	
	//투명 컬러키 셋팅 (배경색 날릴건지, 어떤 색깔)
	LPIMAGE_INFO getImageInfo() { return _imageInfo; }
	bool getIsTrans() const { return _isTrans; }
	COLORREF getTransColor() const { return _transColor; }
	void setTransColor(BOOL isTrans, COLORREF transColor);
	LPIMAGE_INFO getBlendImageInfo() { return _blendImage; }

	//해제
	void release(void);

	//랜더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY,
		int sourWidth, int sourHeight);		//클리핑(자르기) < 미니맵 >

	//알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);	//배경
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);	//배경, 캐릭터
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY,
			int sourWidth, int sourHeight, BYTE alpha);		//클리핑(자르기) 알파랜더

	//프레임 렌더 - deprecated.
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//DC얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	
	//이미지 X좌표
	inline float getX(void) { return _imageInfo->x;}
	inline void setX(float x) { _imageInfo->x = x; }

	//이미지 Y좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//이미지 가로, 세로크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//바운딩 박스 (충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height,
		};
		return rc;
	}

	//바운딩 박스 (충돌용 렉트)
	inline RECT boundingBoxWidthFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight,
		};
		return rc;
	}

	//프레임 X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//프레임 Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	
	//이미지 1 프레임 가로, 세로 크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//최대 프레임 x, y 갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }
	inline int getMaxFrameIdx(void) { return _imageInfo->maxFrameIdx; }

	Image();
	~Image() {}
};

