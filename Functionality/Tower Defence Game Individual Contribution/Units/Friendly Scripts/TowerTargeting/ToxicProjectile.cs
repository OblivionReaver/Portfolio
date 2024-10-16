using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ToxicProjectile : Projectile
{
    private float maxExistance = 5.0f;
    private float existanceTime = 0.0f;

    private float DoT_Cooldown = 1.0f;
    private float DoT_Time = 1.0f;

    void OnEnable()
    {
        radiusSq = radius * radius;
    }

    // Update is called once per frame
    void Update()
    {
        if (!target)
        {
            //Debug.Log("no enemy to target");
            Destroy(gameObject);
            return;
        }

        transform.position = target.position;

        // Check if projectile has excedded its lifespan
        if(existanceTime >= maxExistance)
        {
            Destroy(gameObject);
        } else
        {
            existanceTime += Time.deltaTime;
        }

        // Deal damage over time incrementaly
        if(DoT_Time >= DoT_Cooldown)
        {
            EnemyUnit enemy = target.gameObject.GetComponent<EnemyUnit>();
            if (enemy != null)
            {
                enemy.Health -= damage;
                if (enemy.Health <= 0)
                {
                    enemy.Die();
                    Destroy(gameObject);
                }
            }

            DoT_Time = 0.0f;
        } else
        {
            DoT_Time += Time.deltaTime;
        }
    }

    void OnTriggerEnter2D(Collider2D collider)
    {
        //DO NOTHING
    }

    public static ToxicProjectile Spawn(GameObject prefab, Vector3 position, Quaternion rotation, Transform _target, int _damage)
    {
        GameObject spawnProjectile = Instantiate(prefab, position, rotation);
        ToxicProjectile sp = spawnProjectile.GetComponent<ToxicProjectile>();

        if (!sp)
        {
            sp = spawnProjectile.AddComponent<ToxicProjectile>();
        }

        sp.target = _target;
        damage = _damage;
        return sp;
    }
}
