#pragma once

#define AT_EASETYPE_LINEAR		0
#define AT_EASETYPE_OUT_SINE	1
#define AT_EASETYPE_IN_SINE		2
#define AT_EASETYPE_OUT_CUBIC	3
#define AT_EASETYPE_IN_CUBIC	4
#define AT_EASETYPE_OUT_BACK	5

#define AT_TWEENTYPE_FADE	0
#define AT_TWEENTYPE_MOVE	1
#define AT_TWEENTYPE_SCALE	2

#include "MBUtilities.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <algorithm>

typedef void(*AT_OnCompleteFunc)(void);

typedef struct AT_tweenData_tag
{
	PANEL* panel;
	float alpha;
	float scale_x;
	float scale_y;
	float pos_x;
	float pos_y;
	float time;
	float delay;
	AT_OnCompleteFunc onComplete;
	int easetype;
	int tweenType;

	float _startAlpha;
	float _startTimer;
	float _pos_x;
	float _pos_y;
	float _scale_x;
	float _scale_y;
} AT_tweenData;

typedef std::vector<AT_tweenData> AT_TweenVector;

class AT_PanelComparer
{
public:
	AT_PanelComparer(PANEL* panel) : _panel(panel) {}
	bool operator() (AT_tweenData& data) { return data.panel == _panel; }
private:
	PANEL* _panel;
};

AT_TweenVector AT_tweens;

bool AT_IsFinished(AT_tweenData& data);
void AT_Pan_Fade(AT_tweenData* arg_data);
void AT_Pan_Move(AT_tweenData& arg_data);
void AT_Pan_Scale(AT_tweenData& arg_data);

extern "C"
{
	MBUTILITIES_API void AT_ProcessTweens(float delta_time);
	MBUTILITIES_API void AT_AddTween(AT_tweenData* data);
	MBUTILITIES_API int AT_IsAnyRunning(PANEL* panel);
	MBUTILITIES_API void AT_StopAllOn(PANEL* panel);

	MBUTILITIES_API void AT_ProjectPointOntoLine(VECTOR* a_output, VECTOR* vec_a, VECTOR* vec_b, VECTOR* vec_p);
	MBUTILITIES_API var AT_InverseVecLerp(VECTOR* vec_a, VECTOR* vec_b, VECTOR* vec_p);
	MBUTILITIES_API float AT_lerp(float arg_start, float arg_end, float arg_t);
	MBUTILITIES_API float AT_easeOutBack(float arg_start, float arg_end, float arg_value);
	MBUTILITIES_API float AT_easeInSine(float arg_start, float arg_end, float arg_value);
	MBUTILITIES_API float AT_easeOutSine(float arg_start, float arg_end, float arg_value);
	MBUTILITIES_API float AT_easeInCubic(float arg_start, float arg_end, float arg_value);
	MBUTILITIES_API float AT_easeOutCubic(float arg_start, float arg_end, float arg_value);
	MBUTILITIES_API float AT_inverseLerp(float arg_start, float arg_end, float arg_value);
	MBUTILITIES_API void AT_pan_scale_from_center(PANEL* arg_panel, var arg_scale);
}