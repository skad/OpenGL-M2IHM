#include "world.h"
using namespace std;

World::World(double size)
{
	this->Wind = 0;
	this->nbEoliene = 0;
	this->Size = size;
	this->Orientation_Wind = 0;
	this->fog = true;
}

World::~World()
{
}

void World::SetWind(double Wind) {
	if(debug){cout<<"Force du  vent : "<< Wind<<endl;}
	this->Wind = Wind;
}
double World::GetWind() const {
	return Wind;
}
void World::SetDebug(bool debug) {
	this->debug = debug;
}
bool World::IsDebug() const {
	return debug;
}

double World::GetSize() const {
	return this->Size;
}
	
void  World::SetOrientationWind(int Orientation_Wind)
{
	this->Orientation_Wind = (this->Orientation_Wind+Orientation_Wind)%360;
	if (debug){cout<<"Orientation du vent :"<<this->Orientation_Wind<<endl;}
}

int World::GetOrientationWind() const
{
	return Orientation_Wind;
}

void World::LoadWorld()
{
	//Ajout de la skybox
	double Demi_Size = this->Size/2;
	Sky = SkyBox(-Demi_Size,-Demi_Size,Demi_Size,this->Size);
	Sky.SetDebug(this->debug);
	Sky.SetDataDir(this->Data_Dir);
	Sky.Load();
	//Ajout du sol
	Sol.SetDebug(debug);
	Sol.SetSizeWordl(this->Size);
	Sol.SetDataDir(this->Data_Dir);
	Sol.Load();
	AddEoliene();
	//Ajout de la fleche
	Arrow = Fleche();

	InitFog();
}

void World::InitFog()
{
	GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f}; 
	glFogi (GL_FOG_MODE, GL_LINEAR) ;
	glFogfv(GL_FOG_COLOR,fogColor) ;
	glFogf(GL_FOG_DENSITY, 0.35) ;
	glFogf(GL_FOG_START, 512.0) ;
	glFogf(GL_FOG_END, 1024.0) ;
}

void World::FogOn()
{
	fog = true;
	if (debug){cout<<"Changement etat brouillard : "<<fog <<endl;}
}

void World::FogOff()
{
	fog = false;
	if (debug){cout<<"Changement etat brouillard : "<<fog <<endl;}
}

void World::ChangeSkybox(int num)
{
	Sky.LoadTexture(num);
}
void World::Draw(double camX,double camY,double camZ)
{
	if (fog){glEnable(GL_FOG);}else{glDisable(GL_FOG);}
	this->DrawObject(camX,camY,camZ);

}

void World::RemoveEoliene()
{
	if(nbEoliene >0)
	{
		ListeEolien.pop_back();
		nbEoliene--;
		if(debug){cout<<"Suppression de la derniere eolienne"<<endl;}
	}
}

void World::AddEoliene()
{
	double rayon = RandFloat(0.0,this->Size/2);
	double angle = RandFloat(0.0,360.0);
	double X = 0 + rayon*cos(angle);
	double Z = 0 + rayon*sin(angle);
	nbEoliene++;
	if(debug){
		cout<<"Ajout d'une eolienne en X: "<<X<<" Z: "<<Z<<endl;
	}
	ListeEolien.push_back(Eolien(X,Sol.GetHauteurPos(X,Z),Z));
	ListeEolien.back().SetZoom(Sol.GetMapScale());

}

void World::DrawObject(double camX,double camY,double camZ)
{
	//Affichange de la skybox
	Sky.Draw();
	//Affichange du sol
	Sol.Draw();
	//affichage de la fleche
	Arrow.Draw(camX,camY,camZ,this->Orientation_Wind);
	//Boucle affichages objects
	for(size_t i=0;i<ListeEolien.size();++i)
	{
		ListeEolien[i].Draw(this->Wind,this->Orientation_Wind);
	}
}

void World::ChangeTextureMap(int num)
{
	Sol.TextureNice();
	if(num == 0){Sol.TexureCrapy();}
}
