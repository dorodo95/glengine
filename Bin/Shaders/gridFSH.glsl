#version 330 core

//Grid Logic based on discussion from https://forum.unity.com/threads/antialiased-grid-lines-fwidth.1010668/.
//Thanks to the folks at the Computação Gráfica discord server and Eduardo Righi for the idea!

//TODO: Move this to interface blocks
in vec2 iUV;
in vec3 iNormal;
in vec3 iWorldPos;

uniform sampler2D mainTex;
uniform sampler2D overlayTex;

//TODO: move to a helper file
float invLerp(float a, float b, float val)
{
	return (val - a) / (b - a);
};

//TODO: mask based on camera position instead of world origin
float Mask(float radius)
{	
	float circle;
	circle = distance(vec2(0.0), iWorldPos.xz) / radius;
	circle = 1 - circle;
	circle = clamp(circle,0,1);
	circle *= circle;
	return circle;
}

float RangedDepth(float range, float intensity, float bias)
{
	float worldDepth = gl_FragCoord.z / gl_FragCoord.w; //World Space Depth

	//Remap Depth
	worldDepth /= range;
	worldDepth  = clamp(worldDepth, 0, 1);
	worldDepth *= worldDepth; //Exponential Falloff
	worldDepth -= bias;
	worldDepth  = clamp(worldDepth, 0, 1);
	worldDepth *= intensity;

	return worldDepth;
}

//Regular Grid Rendering
float WorldDerivativeGrid(float tiling, float width)
{
	width = 1 - width;
	vec3  distanceGridAxis  = abs(fract(iWorldPos * tiling) - 0.5) * 2.0; //Creates a Triangle Wave distance field per axis
	float distanceFieldGrid = max(distanceGridAxis.x, distanceGridAxis.z); //Flatten X and Z to calculate everything in a single mask
	float derivative = fwidth(distanceFieldGrid) / 2; //Get derivative range on fragments rendered
	
	//Inverse Lerp Mask
	float a = width - derivative; //First threshold
	float b = width + derivative;
	float grid = invLerp(a,b, distanceFieldGrid);
	grid = clamp(grid, 0.0, 1.0);
	
	return grid;
}

//Grid Points Rendering (Similar to grid function, but with an additional distance field for negative masking
float WorldDerivativePoints(float tiling, float markerSizeBias, float width)
{
	width = 1 - width;
	vec3  distanceGridAxis  = abs(fract(iWorldPos * tiling) - 0.5) * 2.0;
	float distanceFieldGridMax = max(distanceGridAxis.x, distanceGridAxis.z);
	float distanceFieldGridMin = min(distanceGridAxis.x, distanceGridAxis.z); //Get Min as well to get a secondary distance field mask
	float derivative = fwidth(distanceFieldGridMin) / 2;
	
	float a = width - derivative;
	float b = width + derivative;

	float gridMax = invLerp(a,b, distanceFieldGridMax);
	float gridMin = invLerp(a - markerSizeBias,b - markerSizeBias, distanceFieldGridMin); //The larger the bias, the larger the point markers will be
	gridMax = clamp(gridMax, 0.0, 1.0);
	gridMin = clamp(gridMin, 0.0, 1.0);
	gridMax *= gridMin; //Mask out secondary mask negative areas from grid
	
	return gridMax;
}

//Grid Axis Rendering (Similar to Grid rendering, but limited to a single segment
vec2 WorldDerivativeAxis(float width)
{
	width = 1 - width;
	vec3  distanceGridAxis  = abs(fract(iWorldPos) - 0.5) * 2.0;
	
	//Mask out anything outside of the -0.5 to 0.5 range
	distanceGridAxis.x *= step(abs(iWorldPos.x), 0.5);
	distanceGridAxis.z *= step(abs(iWorldPos.z), 0.5);
	
	float derivativeX = fwidth(distanceGridAxis.x) / 2;
	float derivativeZ = fwidth(distanceGridAxis.z) / 2;
	
	//2 derivatives, since we need to keep both axis separated
	float aX = width - derivativeX;
	float bX = width + derivativeX;
	
	float aZ = width - derivativeZ;
	float bZ = width + derivativeZ;

	float gridX = invLerp(aX,bX, distanceGridAxis.x);
	float gridZ = invLerp(aZ,bZ, distanceGridAxis.z);
	gridX = clamp(gridX, 0.0, 1.0);
	gridZ = clamp(gridZ, 0.0, 1.0);
	
	return vec2(gridZ, gridX); //Flip them, since each a line on the X-axis requires points plotted along the Z-Axis and vice-versa
}

//TODO - use opacity and alpha blending for grid instead of solid colors that match the background
void main()
{
	vec2 axisGrid = WorldDerivativeAxis(0.01);
	float majorGrid = WorldDerivativePoints(1, 0.05, 0.02);
	float minorGrid = WorldDerivativeGrid(10, 0.035);
	
	//Tinting
	minorGrid *= 0.3;
	float grid = max(majorGrid, minorGrid);
	grid *= 0.8;
	grid *= Mask(10);

	vec4 col = mix( vec4(25.0/255.0, 25/255.0, 38/255.0, 1.0), vec4(129.0/255.0, 99.0/255.0, 80.0/255.0, 1.0), grid);
	
	col = mix(col, vec4(0.8,0.1,0.3,1), axisGrid.x);	//X Axis
	col = mix(col, vec4(0.02,0.4,0.9,1), axisGrid.y);	//Z Axis
	col += min(axisGrid.x, axisGrid.y);					//Origin Point
	
	gl_FragColor = col;
}