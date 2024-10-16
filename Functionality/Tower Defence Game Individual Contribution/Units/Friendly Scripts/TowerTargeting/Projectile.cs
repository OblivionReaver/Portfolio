using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Projectile : MonoBehaviour
{
    public float movementSpeed = 5.5f;

    protected static int damage;
    protected float radius = 1.0f;
    protected float radiusSq;

    protected Transform target;

    void OnEnable()
    {
        radiusSq = radius * radius;
    }

    // Update is called once per frame
    void Update()
    {
        if(!target)
        {
            //Debug.Log("no enemy to target");
            Destroy(gameObject);
            return;
        }

        Vector3 direction = target.position - this.transform.position;
        transform.position += direction.normalized * movementSpeed * Time.deltaTime;
    }

    void OnTriggerEnter2D(Collider2D collider)
    {
        if(collider.gameObject.tag.Equals("Enemy"))
        {
            EnemyUnit enemy = collider.gameObject.GetComponent<EnemyUnit>();
            if(enemy != null)
            {
                enemy.Health -= damage;
                if(enemy.Health <= 0)
                {
                    enemy.Die();
                }
            }
            Destroy(gameObject);
        }
    }

    public static Projectile Spawn(GameObject prefab, Vector3 position, Quaternion rotation, Transform _target, int _damage)
    {
        GameObject spawnProjectile = Instantiate(prefab, position, rotation);
        Projectile sp = spawnProjectile.GetComponent<Projectile>();

        if(!sp)
        {
            sp = spawnProjectile.AddComponent<Projectile>();
        }

        sp.target = _target;
        damage = _damage;
        return sp;
    }
}
