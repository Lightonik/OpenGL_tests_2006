#define MAX_PARTICLES 4096
//---------------------------------------------------------------------------
class Particle {
        public:
                void Create(Vector *position, float speed, int direction, Vector &force,
                                int lifetime, float weight, int listID, int texture);
                void Move(Vector *pos);
                void Render();
                bool Is();
                Vector position;
        private:
                Vector speed;
                float speedM;
                Vector direction;
                Vector force;
                float weight;
                int lifetime;
                int lifelast;
                int listID;
                int texture;
                float angel;
};
//---------------------------------------------------------------------------
bool Particle::Is() {
        if(lifelast>0)
                return true;
        return false;
}
//---------------------------------------------------------------------------
void Particle::Create(Vector *pos, float sp, int dir, Vector &forc,
                                int life, float wei, int lis, int tex) {
        position=*pos;
        direction.z=random(201)-100;
        direction.y=random(201)-100;
        direction.x=random(201)-100;
        direction.Normal();
        speed.x=sp*direction.x;
        speed.y=sp*direction.y;
        speed.z=sp*direction.z;
        force=forc;
        lifetime=life;
        lifelast=random(lifetime);;
        texture=tex;
        weight=wei;
        listID=lis;
        angel=random(360);
        speedM=sp;
}
//---------------------------------------------------------------------------
void Particle::Move(Vector *pos) {
        if(!Is()){
                lifelast=lifetime+random(lifetime);
                position=*pos;
                direction.z=random(201)-100;
                direction.y=random(201)-100;
                direction.x=random(201)-100;
                direction.Normal();
                speed.x=speedM*direction.x;
                speed.y=speedM*direction.y;
                speed.z=speedM*direction.z;
                return;
        }
        speed.x+=force.x/weight;
        speed.y+=force.y/weight;
        speed.z+=force.z/weight;
        position.x+=speed.x;
        position.y+=speed.y;
        position.z+=speed.z;
        lifelast--;
}
//---------------------------------------------------------------------------
void Particle::Render() {
        if(!Is())
                return;
	glDepthMask(false);
        glDisable (GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPushMatrix();
        glTranslatef(position.x,position.y,position.z);
        glRotatef(angel,0,0,1);
        glCallList(1);
        glPopMatrix();
        glEnable (GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDepthMask(true);
}
//---------------------------------------------------------------------------
Particle Spark[MAX_PARTICLES];
