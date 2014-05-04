#include<iostream>
using std::cout;
using std::endl;

struct Vector2{
	float x;
	float y;

	Vector2(float x = 0, float y = 0): x(x), y(y){
		
	}

	friend Vector2 operator+(const Vector2& a, const Vector2& b){
		Vector2 result;
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		return result;
	}

	friend Vector2 operator-(const Vector2& a, const Vector2& b){
		Vector2 result;
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		return result;
	}

	friend Vector2 operator*(float scalar, const Vector2& right){
		Vector2 result;
		result.x = right.x * scalar;
		result.y = right.y * scalar;
		return result;
	}

	friend Vector2 operator*(const Vector2& left, float scalar){
		Vector2 result;
		result.x = left.x * scalar;
		result.y = left.y * scalar;
		return result;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& right){
		cout << "{" << right.x << ", " << right.y << "}";
		return stream;
	}

	inline float Dot(const Vector2& a, const Vector2& b);

	float Length(){
		float length;
		length = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
		return length;
	}

	float LengthSquared(){
		float length;
		length = (std::pow(x, 2) + std::pow(y, 2));
	}

	static Vector2 Normalized(Vector2& a){
		Vector2 normVector;
		float aLength = a.Length();
		
		if(aLength == 0){
			aLength = 0.00000001;
		}

		normVector.x = (a.x / aLength);
		normVector.y = (a.y / aLength);
		return normVector;
	}

	static Vector2 PerpCW(const Vector2& a){
		Vector2 vectorCW;
		vectorCW.x = a.y;
		vectorCW.y = -a.x;
		return vectorCW;
	}

	static Vector2 PerpCCW(const Vector2& a){
		Vector2 vectorCCW;
		vectorCCW.x = -a.y;
		vectorCCW.y = a.x;
		return vectorCCW;
	}

	static Vector2 LERP(const Vector2& a, const Vector2& b, float beta){
		Vector2 lerpVector;
		lerpVector = (((1 - beta) * a) + (beta * b));
		return lerpVector;
	}
};

inline float Dot(const Vector2& a, const Vector2& b){
		float product;
		product = ((a.x * b.x) + (a.y * b.y));
		return product;
	}
