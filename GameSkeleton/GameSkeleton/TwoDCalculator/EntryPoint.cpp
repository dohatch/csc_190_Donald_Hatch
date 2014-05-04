#include "RenderUI.h"
#include "Engine.h"
#include "Vector2.h"

Vector2 left, right, result;

void myBasicVectorEquationCallback(const BasicVectorEquationInfo& data){
	left = Vector2(data.x1, data.y1);
	left = data.scalar1 * left;
	
	right = Vector2(data.x2, data.y2);
	right = data.scalar2 * right;

	if(data.add){
		result = left + right;
	}
	else{
		result = left - right;
	}
}

Vector2 originalVector, normalVector, cwPerpendicularVector, ccwPerpendicularVector;

void myPerpendicularDataCallback(const PerpendicularData& data){
	originalVector = Vector2(data.x, data.y);
	normalVector = Vector2::Normalized(originalVector);
	cwPerpendicularVector = Vector2::PerpCW(originalVector);
	ccwPerpendicularVector = Vector2::PerpCCW(originalVector);
}

Vector2 vector1, vector2, projectionVector, rejectionVector;

void myDotProductDataCallback(const DotProductData& data){
	vector1 = Vector2(data.v1i, data.v1j);
	vector2 = Vector2(data.v2i, data.v2j);

	Vector2 normVect1 = Vector2::Normalized(vector1);
	Vector2 normVect2 = Vector2::Normalized(vector2);

	if(data.projectOntoLeftVector) {
		float cos = Dot(vector2, normVect1);
		projectionVector = cos * (normVect1);
		rejectionVector = vector2 - projectionVector;
	}
	else{
		float cos = Dot(vector1, normVect2);
		projectionVector = cos * (normVect2);
		rejectionVector = vector1 - projectionVector;

		
	}
}

Vector2 aVector, bVector, bMinusAVector, aVectorLerpPortion, bVectorLerpPortion, lerpResultVector;

void myLerpDataCallback(const LerpData& data){
	aVector = Vector2(data.a_i, data.a_j);
	bVector = Vector2(data.b_i, data.b_j);
	bMinusAVector = bVector - aVector;
	aVectorLerpPortion = (Vector2::LERP(aVector, bVector, data.beta) - (bVector * data.beta));
	bVectorLerpPortion = (Vector2::LERP(aVector, bVector, data.beta) - (aVector * (1 - data.beta)));
	lerpResultVector = aVectorLerpPortion + bVectorLerpPortion;
}



int main(int argc, char* argv[])
{
	Engine::Init();

	RenderUI renderUI;

	renderUI.setBasicVectorEquationData(myBasicVectorEquationCallback, (float*)&left, (float*)&right, (float*)&result);
	renderUI.setPerpendicularData((float*)&originalVector, (float*)&normalVector, (float*)&cwPerpendicularVector, (float*)&ccwPerpendicularVector, myPerpendicularDataCallback);
	renderUI.setDotProductData((float*)&vector1, (float*)&vector2, (float*)&projectionVector, (float*)&rejectionVector, myDotProductDataCallback);
	renderUI.setLerpData((float*)&aVector, (float*)&bVector, (float*)&bMinusAVector, (float*)&aVectorLerpPortion, (float*)&bVectorLerpPortion, (float*)&lerpResultVector, myLerpDataCallback);

	if( ! renderUI.initialize(argc, argv))
		return -1;
	return renderUI.run();
}