#pragma once   
   //!!5 for Serialization
class Figure: public CObject 
{
	//!!5 b
	DECLARE_SERIAL(Figure)   //!!! NO ";"     
public:
	DWORD ColorFigure;
	void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);
		if(ar.IsStoring())
		{
			ar << x1;
			ar << x2;
			ar << y1;
			ar << y2;
			ar << ColorFigure;
			//!!7 //ar << KIND;
		}
		else // Loading, not storing
		{
			ar >> x1;
			ar >> x2;
			ar >> y1;
			ar >> y2;
			ar >> ColorFigure;
			//!!7 //ar >> KIND;
		}
	}
	//!!5 e
protected:
public:
	int x1,y1,x2,y2;//!!7 //,KIND;
	Figure();
	Figure(int xx1,int yy1, int xx2, int yy2, DWORD color)
	{
		x1=xx1;
		x2=xx2;
		y1=yy1;
		y2=yy2;
		ColorFigure = color;
	}
         //!!5 for Serialization
        // NOT PURE !!! 
	void SetColor(DWORD FigureColor)
	{
		ColorFigure = FigureColor;
	}
	DWORD GetColor() const 
	{
		return ColorFigure;
	}
	virtual void MouseMove(CPoint, CPoint, CDC*){}
	virtual void Draw(CDC *dc){};
	virtual ~Figure(void);
};

class RectangleM:public Figure
{
	//!!5 b
	DECLARE_SERIAL (RectangleM)   //!!! NO ";"     
	//!!5 e
public:
	RectangleM(); //!!5 must 
	RectangleM(int xx1, int yy1, int xx2, int yy2, DWORD FigureColor) :Figure(xx1, yy1, xx2, yy2, FigureColor)
	{
		//!!7 //KIND=0;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush;
	    myBrush.CreateSolidBrush(ColorFigure);
		dc->SelectObject(&myBrush);
		dc->Rectangle(x1, y1, x2, y2);
	}
};

class Square: public RectangleM
{
	//!!5 b
	DECLARE_SERIAL(Square)   //!!! NO ";"     
	//!!5 e
public:
	Square(); //!!5 must 
	Square(int xx1, int yy1, int xx2, int yy2, DWORD FigureColor) :RectangleM(xx1, yy1, xx2, yy2, FigureColor)
	{
		if (xx1 < xx2)
		{
			x2 = xx1 + abs(yy1 - yy2);
		}
		else
		{
			x2 = xx1 - abs(yy1 - yy2);
		}
		//!!7 //KIND=0;
	}
};

class EllipseM:public Figure
{
	//!!5 b
	DECLARE_SERIAL (EllipseM)   //!!! NO ";"     
	//!!5 e
public:
	EllipseM();  //!!5 must
	EllipseM(int xx1, int yy1, int xx2, int yy2, DWORD FigureColor) :Figure(xx1, yy1, xx2, yy2, FigureColor)
	{
		//!!7 //KIND=1;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush;
		myBrush.CreateSolidBrush(ColorFigure);
		dc->SelectObject(&myBrush);
		dc->Ellipse(x1, y1, x2, y2);
	}
};

class Circle:public EllipseM
{
	//!!5 b
	DECLARE_SERIAL (Circle)   //!!! NO ";"     
	//!!5 e
public:
	Circle();  //!!5 must
	Circle(int xx1,int yy1, int xx2, int yy2,DWORD FigureColor) :EllipseM(xx1,yy1,xx2,yy2,FigureColor)
	{
		if (xx1 < xx2)
		{
			x2 = xx1 + abs(yy1 - yy2);
		}
		else
		{
			x2 = xx1 - abs(yy1 - yy2);
		}
		//!!7 //KIND=1;
	}
};

class Line:public Figure
{
	//!!5 b
	DECLARE_SERIAL (Line)   //!!! NO ";"     
	//!!5 e
public:
	Line();  //!!5 must
	Line(int xx1, int yy1, int xx2, int yy2, DWORD FigureColor) :Figure(xx1, yy1, xx2, yy2, FigureColor)
	{
		//!!7 //KIND=1;
	}
	void Draw(CDC *dc)
	{
		CPen myPen1(PS_SOLID, 3, ColorFigure);
		CPen *oldPen;
		oldPen=dc->SelectObject(&myPen1); 
		dc->SetROP2(R2_NOTXORPEN); 
		dc->MoveTo(x1,y1);
		dc->LineTo(x2,y2);
		dc->SelectObject(oldPen);
	}
};

class Triangle:public Figure
{
	//!!5 b
	DECLARE_SERIAL (Triangle)   //!!! NO ";"     
	//!!5 e
public:
	Triangle();  //!!5 must
	Triangle(int xx1,int yy1, int xx2, int yy2,DWORD FigureColor) :Figure(xx1,yy1,xx2,yy2,FigureColor)
	{
		//!!7 //KIND=1;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush;
	    myBrush.CreateSolidBrush(ColorFigure);
		dc->SelectObject(&myBrush);
		CPoint T[3];
		T[0].x=x1;
		T[0].y=y2;
		T[1].x=x2;
		T[1].y=y2;
		T[2].x=(x1+x2)/2;
		T[2].y=y1;
		dc->Polygon(T,3);
	}
};