public class Assignment2 
{
    /*
     *  NETTRIX CATALOGUE!
     */   
    private String[] catalogue=
    {
        "MOVIE#2001: A Space Odyssey#1968",
        "GAME#The Witcher 3#2015",
        "TV-SERIES#Stranger Things (Season 1)#2016",
        "GAME#Minecraft#2009",
        "ALBUM#All Eyez On Me#1996",
        "MOVIE#Star Trek II: The Wrath of Khan#1982",
        "ALBUM#Hand on the Torch#1993",
        "TV-Series#Black Mirror (Season 1)#2011",
        "GAME#Zork#1980",
        "ALBUM#Fetch the Bolt Cutters#20190",
        "MOVIEZ#The Irishman#2019",
        "GAME#Papers, Please#2013"
    }; 

    /*
     * DO NOT MODIFY THIS METHOD STRUCTURE!
     * FEEL FREE TO MODIFY VALUES FOR myYear AND myTitleType TO TEST METHOD IMPLEMENTATIONS.
     */
    public void run()
    {
        int myYear=1999;
        int myTitleType=0;

        System.out.println("Printing names of existing titles in the catalog...");
        printTitleNames(myTitleType);
        System.out.println("------------");
        if (isThereMusicAfter(myYear))
        {
            System.out.println("There is some music after "+myYear);
        }
        else
        {
            System.out.println("Seriously, there is NO music after "+myYear);
        }

        System.out.println("------------");
        System.out.println("Printing report on catalog format...");
        System.out.println(getFormatReport());
        System.out.println("------------");
        System.out.println("Printing statistics on media release periods...");
        System.out.println(releasedTitlesHistogram());  
    }

    /**
     * Implement Q1, feel free to modify the body of this method
     */
    private void printTitleNames(int titleType)
    {
        //Constants for category types
        final int ALL = 0;
        final int MOVIE = 1;
        final int TV_SERIES = 2;
        final int GAME = 3;
        final int ALBUM = 4;

        for (int i = 0; i < catalogue.length; i++)
        {
            if (titleType == ALL)
            {
                System.out.println(catalogue[i].substring(firstHashtagSearch(catalogue, i) + 1, secondHashtagSearch(catalogue, i)));
            } else if (titleType == MOVIE) {

                if (catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("MOVIE"))
                {
                    System.out.println(catalogue[i].substring(firstHashtagSearch(catalogue, i) + 1, secondHashtagSearch(catalogue, i)));
                }
            } else if (titleType == TV_SERIES) {

                if (catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("TV-SERIES"))
                {
                    System.out.println(catalogue[i].substring(firstHashtagSearch(catalogue, i) + 1, secondHashtagSearch(catalogue, i)));
                }
            } else if (titleType == GAME) {

                if (catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("GAME"))
                {
                    System.out.println(catalogue[i].substring(firstHashtagSearch(catalogue, i) + 1, secondHashtagSearch(catalogue, i)));
                }
            } else if (titleType == ALBUM) {

                if (catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("ALBUM"))
                {
                    System.out.println(catalogue[i].substring(firstHashtagSearch(catalogue, i) + 1, secondHashtagSearch(catalogue, i)));
                }
            } else {
                System.out.println("Invalid Media Type");
            }
        }

    }
    
    /**
     * Implement Q2, feel free to modify the body of this method
     * @return Whether there is music in the catalog released after the 90s
     */
    private boolean isThereMusicAfter(int year) 
    {
        boolean YearCheck = false;

        final int MIN_YEAR = 1920;
        final int MAX_YEAR = 2019;

        int[] Years = new int[catalogue.length];

        for (int i = 0; i < catalogue.length; i++)
        {
            Years[i] = Integer.parseInt(catalogue[i].substring(secondHashtagSearch(catalogue, i) + 1, catalogue[i].length()));
            if (year >= MIN_YEAR && year <= MAX_YEAR)
            {
                if (catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("ALBUM") && Years[i] >= MIN_YEAR && Years[i] > year && Years[i] <= MAX_YEAR)
                    {
                        YearCheck = true;
                    }
            }
        }
                    
        return YearCheck;
    }

    /**
     * Implement Q3, feel free to modify the body of this method
     * @return A report on format validity of the provided catalogue.
     */
    private String getFormatReport()
    {
        StringBuilder FormatChecker = new StringBuilder();
        int[] Years = new int[catalogue.length];
        final int MIN_YEAR = 1920;
        final int MAX_YEAR = 2019;

        for (int i = 0; i < catalogue.length; i++)
        {
            Boolean CorrectType = false;
            Boolean CorrectYear = false;

            Years[i] = Integer.parseInt(catalogue[i].substring(secondHashtagSearch(catalogue, i) + 1, catalogue[i].length()));

            if (catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("MOVIE")||catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("TV-SERIES")||catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("GAME")||catalogue[i].substring(0,firstHashtagSearch(catalogue, i)).equals("ALBUM"))
            {
                CorrectType = true;
            }

            if (Years[i] >= MIN_YEAR && Years[i] <= MAX_YEAR)
            {
                CorrectYear = true;
            }

            if (CorrectType && CorrectYear)
            {
                FormatChecker.append("Item #" + (i + 1) + " - OK.\n");
            } else if (!CorrectType && CorrectYear) {
                FormatChecker.append("Item #" + (i + 1) + " - incorrect media type.\n");
            } else if (CorrectType && !CorrectYear) {
                FormatChecker.append("Item #" + (i + 1) + " - year incorrect or out of range.\n");
            } else {
                FormatChecker.append("Item #" + (i + 1) + " - incorrect media type, year incorrect or out of range.\n");
            }
        }

        return FormatChecker.toString();
    }

    /**
     * Implement Q4, feel free to modify the body of this method
     */
    private String releasedTitlesHistogram()
    {
        String Histogram = "";
        int[] Years = new int[catalogue.length];

        //Constants for year ranges
        final int NINETEEN_TWENTY = 1920;
        final int NINETEEN_FOURTY_FOUR = 1944;
        final int NINETEEN_FOURTY_FIVE = 1945;
        final int NINETEEN_SIXTY_NINE = 1969;
        final int NINETEEN_SEVENTY = 1970;
        final int NINETEEN_NINETY_FOUR = 1994;
        final int NINETEEN_NINETY_FIVE = 1995;
        final int TWENTY_NINETEEN = 2019;

        int Range1 = 0;
        int Range2 = 0;
        int Range3 = 0;
        int Range4 = 0;

        for (int i = 0; i < catalogue.length; i++)
        {
            Years[i] = Integer.parseInt(catalogue[i].substring(secondHashtagSearch(catalogue, i) + 1, catalogue[i].length()));

            if (Years[i] >= NINETEEN_TWENTY && Years[i] <= NINETEEN_FOURTY_FOUR)
            {
                Range1++;
            } else if (Years[i] >= NINETEEN_FOURTY_FIVE && Years[i] <= NINETEEN_SIXTY_NINE) {
                Range2++;
            } else if (Years[i] >= NINETEEN_SEVENTY && Years[i] <= NINETEEN_NINETY_FOUR) {
                Range3++;
            } else if (Years[i] >= NINETEEN_NINETY_FIVE && Years[i] <= TWENTY_NINETEEN) {
                Range4++;
            }
        }

        String NewLine = "\n";
        Histogram = "Number of titles in 1920-1944: " + Range1 + NewLine + "Number of titles in 1945-1969: " + Range2 + NewLine + "Number of titles in 1970-1994: " + Range3 + NewLine + "Number of titles in 1995-2019: " + Range4;

        return Histogram;
    }  

    //method for finding the first hashtag in some element of the array (useful for finding the category (eg. MOVIE))
    private int firstHashtagSearch(String[] Search, int i)
    {
        int hashtag = Search[i].indexOf("#");

        return hashtag;
    }

    //method for finding the second hashtag in some element of the array (useful for finding the max index of the name, and the minimum index for the year)
    private int secondHashtagSearch(String[] Search, int i)
    {
        int hashtag = Search[i].indexOf("#", firstHashtagSearch(Search, i) + 1);
        
        return hashtag;
    }
}