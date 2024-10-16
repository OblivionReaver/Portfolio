using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightningBuilding : ABuilding
{
    public GameObject firstLightning;
    public GameObject secondLightning;
    public GameObject thirdLightning;

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
            Debug.Log("spawning projectile");
            int firstTarget = (int) Random.Range(0, EnemiesInRange.Count);
            int secondTarget = (int) Random.Range(0, EnemiesInRange.Count);
            int thirdTarget = (int) Random.Range(0, EnemiesInRange.Count);

            LightningProjectile first = LightningProjectile.Spawn(firstLightning, this.transform.position, this.transform.rotation, EnemiesInRange[firstTarget].transform, MDamage);
            LightningProjectile second = LightningProjectile.Spawn(secondLightning, this.transform.position, this.transform.rotation, EnemiesInRange[secondTarget].transform, MDamage);
            LightningProjectile third = LightningProjectile.Spawn(thirdLightning, this.transform.position, this.transform.rotation, EnemiesInRange[thirdTarget].transform, MDamage);

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
        }
        else
        {
            fireRate = AttackCooldown;
        }
    }
}
