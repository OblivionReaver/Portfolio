using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightningProjectile : MonoBehaviour
{
    public float movementSpeed = 5.5f;
    private static int damage;

    private int chainChance = 100;
    private float radius = 1.0f;
    private float radiusSq;

    private Transform target;

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

        Vector3 direction = target.position - this.transform.position;
        transform.position += direction.normalized * movementSpeed * Time.deltaTime;
    }

    void OnTriggerEnter2D(Collider2D collider)
    {
        if (collider.gameObject.tag.Equals("Enemy"))
        {
            EnemyUnit enemy = collider.gameObject.GetComponent<EnemyUnit>();
            if (enemy != null)
            {
                enemy.Health -= damage;
                if (enemy.Health <= 0)
                {
                    enemy.Die();
                }

                List<Collider2D> tmp = new List<Collider2D>(
                    Physics2D.OverlapCircleAll(collider.transform.position, 5)
                    );

                List<Collider2D> newTargets = new List<Collider2D>();
                foreach(Collider2D collision in tmp)
                {
                    if(collision.gameObject.tag.Equals("Enemy") && collision.gameObject.transform != target)
                    {
                        newTargets.Add(collision);
                    }
                }

                if (tmp.Count > 0)
                {
                    int randomTarget = (int)Random.Range(0, newTargets.Count);
                    int chainProbability = (int)Random.Range(0, 100);

                    if(chainProbability < chainChance)
                    {
                        target = newTargets[randomTarget].transform;
                        //chainChance -= 10;
                    } else
                    {
                        Destroy(gameObject);
                    }
                } else
                {
                    Destroy(gameObject);
                }

            }
        }
    }

    public static LightningProjectile Spawn(GameObject prefab, Vector3 position, Quaternion rotation, Transform _target, int _damage)
    {
        GameObject spawnProjectile = Instantiate(prefab, position, rotation);
        LightningProjectile sp = spawnProjectile.GetComponent<LightningProjectile>();

        if (!sp)
        {
            sp = spawnProjectile.AddComponent<LightningProjectile>();
        }

        sp.target = _target;
        damage = _damage;
        return sp;
    }
}
