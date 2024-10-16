using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TowerButtons : MonoBehaviour
{
    public GameObject TowerPanel;
    public GameObject TowerInfoPanel;
    public GameManager gm;
    public GameObject upgradeCanvas;

    [SerializeField] private GameObject TowerPrefab;

    private void Start()
    {
        gm = GameObject.FindGameObjectWithTag("GameManager").GetComponent<GameManager>();
    }

    public void ToggleTowerPanel()
    {
        if (!TowerPanel.activeSelf)
        {
            TowerPanel.SetActive(true);
        }
        else
        {
            TowerPanel.SetActive(false);
        }
    }

    public void SelectTower()
    {
        if(!TowerInfoPanel.activeSelf)
        {
            DisableInfoPanels();
            gm.SetSelectedTower(TowerPrefab);
            EnableInfoPanels(TowerInfoPanel.GetComponent<Transform>());

            if (upgradeCanvas.activeSelf)
            {
                upgradeCanvas.SetActive(false);
            }
        }
    }

    public void DeselectTower()
    {
        gm.ResetTower();
        TowerInfoPanel.SetActive(false);
    }

    private void DisableInfoPanels()
    {
        GameObject info_canvas = GameObject.Find("Info_Canvas");
        foreach(Transform panel in info_canvas.GetComponentsInChildren<Transform>())
        {
            if(panel.gameObject.name != "Info_Canvas")
            {
                if (panel.gameObject.activeSelf)
                {
                    panel.gameObject.SetActive(false);
                }
            }
        }
    }

    private void EnableInfoPanels(Transform panel)
    {
        panel.gameObject.SetActive(true);
        foreach (Transform child in panel)
        {
            EnableInfoPanels(child);
        }
    }
}
