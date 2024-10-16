using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayButton : MonoBehaviour
{
    private LevelManager lm;

    // Start is called before the first frame update
    void Start()
    {
        lm = GameObject.FindGameObjectWithTag("LevelManager").GetComponent<LevelManager>();
    }

    public void PlayPressed()
    {
        lm.SendWave();
    }
}
