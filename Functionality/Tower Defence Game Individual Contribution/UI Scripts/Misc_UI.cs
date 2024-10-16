using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class Misc_UI : MonoBehaviour
{
    public TextMeshProUGUI moneyText;
    public TextMeshProUGUI healthText;
    public Slider healthBar;
    
    private GameManager gm;

    // Start is called before the first frame update
    void Start()
    {
        gm = GameObject.FindGameObjectWithTag("GameManager").GetComponent<GameManager>();
    }

    // Update is called once per frame
    void Update()
    {
        moneyText.text = "$ " + gm.Money.ToString();
        healthText.text = gm.Lives.ToString() + " / 100";
        healthBar.value = gm.Lives;
    }
}
