using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeathRayBuilding : ABuilding
{
    private float DoT_Time;

    void Awake()
    {
        DoT_Time = AttackCooldown;
    }

    public override void Attack()
    {
        //throw new System.NotImplementedException();

        // Deal damage over time every increment of set time
        if (DoT_Time >= AttackCooldown)
        {
            for (int i = 0; i < EnemiesInRange.Count; i++)
            {
                EnemyUnit enemy = EnemiesInRange[i].gameObject.GetComponent<EnemyUnit>();
                if (enemy != null)
                {
                    enemy.Health -= MDamage;
                    if (enemy.Health <= 0)
                    {
                        enemy.Die();
                    }
                }
            }

            DoT_Time = 0.0f;
        }
        else
        {
            DoT_Time += Time.deltaTime;
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
        }
        else
        {
            DoT_Time = AttackCooldown;
        }
    }
}
