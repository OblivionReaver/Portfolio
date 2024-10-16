using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UpgradeHUD : MonoBehaviour
{
    private GameManager gm;
    public GameObject selectedTower;
    private ABuilding towerScript;
    private int sellCost;

    [SerializeField] private GameObject upgradeCanvas;
    [SerializeField] private Image towerImage;
    [SerializeField] private TextMeshProUGUI towerName;
    [SerializeField] private TextMeshProUGUI healthText;
    [SerializeField] private TextMeshProUGUI attackText;
    [SerializeField] private TextMeshProUGUI sellCostText;
    [SerializeField] private TextMeshProUGUI upgradeCostText;


    // Start is called before the first frame update
    void Start()
    {
        selectedTower = null;
        towerScript = null;
        sellCost = 0;

        if(upgradeCanvas.activeSelf)
        {
            upgradeCanvas.SetActive(false);
        }

        gm = GameObject.FindGameObjectWithTag("GameManager").GetComponent<GameManager>();
    }

    public void updateHUD(GameObject _selectedTower)
    {
        selectedTower = _selectedTower;
        towerScript = _selectedTower.GetComponent<ABuilding>();

        if(towerScript != null)
        {
                upgradeCanvas.SetActive(true);
                towerImage.sprite = selectedTower.GetComponent<SpriteRenderer>().sprite;
                towerName.text = selectedTower.name;
                healthText.text = towerScript.Health.ToString();
                attackText.text = towerScript.MDamage.ToString();

                sellCost = (int) towerScript.Cost / 2;

                sellCostText.text = "Sell (" + sellCost.ToString() + ")";
                upgradeCostText.text = "Upgrade (" + towerScript.UpgradeCost.ToString() + ")";
        }
    }

    public void sellTower()
    {
        if(selectedTower != null && towerScript != null)
        {
            if(sellCost > 0)
            {
                gm.Money += sellCost;
                upgradeCanvas.SetActive(false);

                Destroy(selectedTower);
            }
        }
    }

    public void upgradeTower()
    {
        if (selectedTower != null && towerScript != null)
        {
            if(towerScript.UpgradeCost > 0 && gm.Money >= towerScript.UpgradeCost)
            {
                gm.SpendMoney(towerScript.UpgradeCost);
                towerScript.Cost += towerScript.UpgradeCost;
                towerScript.MDamage *= 2;
                towerScript.Health += 100;
                towerScript.UpgradeCost = (int)towerScript.Cost/2;

                updateHUD(selectedTower);
            }
        }
    }

    public void cancelUpgrade()
    {
        upgradeCanvas.SetActive(false);
        selectedTower = null;
        towerScript = null;
    }
}
