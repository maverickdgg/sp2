#include "SpaceVehicles.h"

size_t SpaceVehicles::SV_count = 0;

SpaceVehicles::SpaceVehicles() : max_speed(25)
{
	SV_count++;
	b_vehDebounce = false;
	b_isInVehicle = false;
	lap = 0;
	lapDebounce = false;
}

SpaceVehicles::SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos , int max_speed) : GameObject(object_name, boundary, viewAngle, pos), acceleration(25), speed(0), max_speed(max_speed), rotateAngle(80)
{
	b_vehDebounce = false;
	b_isInVehicle = false;
	rotationZ = 0;
	lap = 0;
	lapDebounce = false;
}

SpaceVehicles::~SpaceVehicles()
{
	SV_count--;
}


void SpaceVehicles::updateVehicle(double deltaTime)
{
	if (Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
    {
        if (speed < max_speed)
        {
            speed += acceleration * deltaTime;
        }
		if (speed>max_speed)
		{
			speed = max_speed;
		}
    }

	if (Application::IsKeyPressed('S') && !Application::IsKeyPressed('W'))
    {
        if (speed > -max_speed)
        {
            speed -= acceleration * deltaTime;
        }
		if (speed < -max_speed)
		{
			speed = -max_speed;
		}
    }
	else if (!Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
    {
		if (speed > -2 && speed <2)
		{
			speed = 0;
		}
        if (speed > 0)
        speed -= acceleration * deltaTime;

		if (speed < 0)
		{
			speed += acceleration * deltaTime;
		}

    }
   
	if (Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
    {
		//if (rotationZ <= 0)
		//{
			viewAngle += rotateAngle * deltaTime;

        
		if (rotationZ > -45)
			rotationZ -= rotateAngle * 2* deltaTime;
		else if (rotationZ < -45)
			rotationZ = -45;
    }
	if (Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
    {
		//if (rotationZ >= 0)
		//{
			viewAngle -= rotateAngle * deltaTime;
		
		if (rotationZ < 45)
			rotationZ += rotateAngle* 2 * deltaTime;
		else if (rotationZ > 45)
			rotationZ = 45;
    }
	if (!Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
	{
		if (rotationZ > -5 && rotationZ < 5)
		{
			rotationZ = 0;
		}
		if (rotationZ > 0)
		{
			rotationZ -= rotateAngle* deltaTime;
		}
		if (rotationZ < 0)
		{
			rotationZ += rotateAngle * 2* deltaTime;
		}
	}
        pos.x += sin(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
        pos.z += cos(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;

}



void SpaceVehicles::updateVehicle(double deltaTime , PMAP map,queue<int>& q)
{

	if (collision(pos, indexToVector(q.front()), 40))
	{
		q.push(q.front());
		q.pop();
	}
	if (Application::IsKeyPressed('W') && !Application::IsKeyPressed(VK_SPACE))
	{
		if (speed < max_speed)
		{
			speed += acceleration * deltaTime;
		}
		if (speed>max_speed)
		{
			speed = max_speed;
		}
	}

	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (speed > 0)
		{
			speed -= acceleration *1.5* deltaTime;
		}

	}
	else if (!Application::IsKeyPressed('W') && !Application::IsKeyPressed(VK_SPACE))
	{
		if (speed > -2 && speed <2)
		{
			speed = 0;
		}
		if (speed > 0)
			speed -= acceleration * deltaTime;
		if (speed < 0)
		{
			speed += acceleration * deltaTime;
		}
	}

	if (Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
	{
		//if (rotationZ <= 0)
		//{
		viewAngle += rotateAngle * deltaTime;


		if (rotationZ > -45)
			rotationZ -= rotateAngle * 2 * deltaTime;
		else if (rotationZ < -45)
			rotationZ = -45;
	}
	if (Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
	{
		//if (rotationZ >= 0)
		//{
		viewAngle -= rotateAngle * deltaTime;

		if (rotationZ < 45)
			rotationZ += rotateAngle * 2 * deltaTime;
		else if (rotationZ > 45)
			rotationZ = 45;
	}
	if (!Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
	{
		if (rotationZ > -5 && rotationZ < 5)
		{
			rotationZ = 0;
		}
		if (rotationZ > 0)
		{
			rotationZ -= rotateAngle* deltaTime;
		}
		if (rotationZ < 0)
		{
			rotationZ += rotateAngle * 2 * deltaTime;
		}
	}
	Vector3 tempPos = pos;
	 
	tempPos.x += sin(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
	tempPos.z += cos(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
	if (map->data[vectorToIndex(tempPos)] != '1')
	{
		pos = tempPos;
	}
	else
	{
		if (speed > 25)
		{
			speed -= acceleration * 6 * deltaTime;
		}
		
		if (speed < 0)
		{
			speed = 0;
		}
		if (map->data[vectorToIndex(Vector3(tempPos.x, 0, pos.z))] != '1')
		{
			pos.x = tempPos.x;
		}
		else if (map->data[vectorToIndex(Vector3(pos.x, 0, tempPos.z))] != '1')
		{
			pos.z = tempPos.z;
		}
	}

	if (map->data[vectorToIndex(pos)] == '3' && lapDebounce==false)
	{
		lapDebounce = true;
		++lap;
	}
	if (lapDebounce == true && map->data[vectorToIndex(pos)] != '3')
	{
		lapDebounce = false;
	}
}

void SpaceVehicles::enterVehicleUpdate(Player& player)
{
	if (Application::IsKeyPressed('E') && b_vehDebounce == false && b_isInVehicle == false && collision(player, this->pos, this->boundary + player.boundary + 10))
	{
		b_isInVehicle = true;
		b_vehDebounce = true;
	}
	else if (Application::IsKeyPressed('E') && b_vehDebounce == false && b_isInVehicle == true)
	{
		b_isInVehicle = false;
		b_vehDebounce = true;
		player.pos = this->pos - Vector3(11, 0, 10);
	}
	if (!Application::IsKeyPressed('E') && b_vehDebounce == true)
	{
		b_vehDebounce = false;
	}
}

void SpaceVehicles::updateCPUVehicle(double deltaTime, PMAP map, queue<int>& q)
{
	Vector3 target = indexToVector(q.front());
	if (collision(pos,indexToVector(q.front()), 20))
	{
		q.push(q.front());
		q.pop();
	}
	Vector3 view = (target - pos).Normalized();
	view = Vector3(view.x, 0, view.z);

	if (view.z >= 0)
		viewAngle = Math::RadianToDegree(atan(view.x / view.z)) ;
	else
		viewAngle = Math::RadianToDegree(atan(view.x / view.z)) - 180 ;


	// moving the vehicle based on the view angle gotten from target
	if (speed < max_speed)
	{
		speed += acceleration * deltaTime;
	}
	if (speed>max_speed)
	{
		speed = max_speed;
	}
	Vector3 tempPos = pos;

	tempPos.x += sin(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
	tempPos.z += cos(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
	if (map->data[vectorToIndex(tempPos)] != '1')
	{
		pos = tempPos;
	}
	else
	{
		if (speed > 25)
		{
			speed -= acceleration * 6 * deltaTime;
		}

		if (speed < 0)
		{
			speed = 0;
		}
		if (map->data[vectorToIndex(Vector3(tempPos.x, 0, pos.z))] != '1')
		{
			pos.x = tempPos.x;
		}
		else if (map->data[vectorToIndex(Vector3(pos.x, 0, tempPos.z))] != '1')
		{
			pos.z = tempPos.z;
		}
	}
	if (map->data[vectorToIndex(pos)] == '3' && lapDebounce == false)
	{
		lapDebounce = true;
		++lap;
	}
	if (lapDebounce == true && map->data[vectorToIndex(pos)] != '3')
	{
		lapDebounce = false;
	}
}

int SpaceVehicles::getRacePosition(SpaceVehicles x,int startIndex)
{
	//x is the opponent vehicle
	if (x.lap > this->lap)
	{
		return 2;
	}
	else if (x.lap < this->lap)
	{
		return 1;
	}
	else
	{
		int thisCheckpoint =racepath.size()- this->positionInQueue(startIndex);
		int xCheckpoint = racepath.size() - x.positionInQueue(startIndex);
		if (thisCheckpoint < xCheckpoint)
		{
			return 2;
		}
		else if (thisCheckpoint >xCheckpoint)
		{
			return 1;
		}
		else
		{
			if (this->distanceFromCheckpoint() > x.distanceFromCheckpoint())
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
	}
}

int SpaceVehicles::positionInQueue(int index)
{
	queue<int> copy = this->racepath;
	int pos = 0;
	while (copy.front() != index)
	{
		if (copy.empty())
		{
			pos = -1;
			break;
		}
		++pos;
		copy.pop();
	}
	return pos; 
}

float SpaceVehicles::distanceFromCheckpoint()
{
	Vector3 checkpoint = indexToVector(racepath.front());
	Vector3 distance = pos - checkpoint;
	return distance.Length();
}