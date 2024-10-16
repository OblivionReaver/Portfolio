using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ToxicBuilding : ABuilding
{
    public GameObject ProjectilePrefab;

    private float fireRate;

    void Awake()
    {
        fireRate = AttackCooldown;
    }

    public override void Attack()
    {
        //throw new System.NotImplementedException();

        // Fire a bullet every [AttackCooldown] seconds
        if (fireRate >= AttackCooldown)
        {
            for(int i = 0; i < EnemiesInRange.Count; i++)
            {
                Debug.Log("spawning projectile");
                Projectile p = Projectile.Spawn(ProjectilePrefab, this.transform.position, this.transform.rotation, EnemiesInRange[i].transform, MDamage);
            }

            fireRate = 0.0f;
        }
        else
        {
            fireRate += Time.deltaTime;
        }
    }

    public override void Die()
    {
        throw new System.NotImplementedException();
    }

    protected override void Update()
    {
        //throw new System.NotImplementedException();

        if (EnemiesInRange.Count > 0)
        {
            Attack();
        } else
        {
            fireRate = AttackCooldown;
        }
    }
}
