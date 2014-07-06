import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Dictionary;
import java.util.Hashtable;
import java.util.Scanner;
import java.util.Vector;

/**
 * Created by Alex on 1/23/14.
 */
public class Main {
    // Instance vars
    private String strFileName;
    private static Vector<String> lstData;
    private static double[][] aiAdjMat;
    private static double[] adExchangeRates;
    private static Dictionary<String, Integer> dictCorresp;
    private static Vector<String> lstReverseCorresp;

    // Methods
    // Constructor
    public Main(String FileName) {
        strFileName = FileName;
        lstData = new Vector<String>();
        aiAdjMat = null;
        dictCorresp = new Hashtable<String, Integer>();
        lstReverseCorresp = new Vector<String>();
    }

    public static void main(String[] args) throws IOException {
        Main parser = new Main("Exchange.txt");
        parser.processLineByLine();
        parser.parseAndAddLine();
        aiAdjMat = new double[dictCorresp.size()][dictCorresp.size()];
        parser.fillAdjMat();
        Dijkstra.doDijkstra(aiAdjMat, dictCorresp, lstReverseCorresp);
    }

    public final void processLineByLine() throws IOException {
        try (Scanner scanner = new Scanner(new File(strFileName), StandardCharsets.UTF_8.name())) {
            while (scanner.hasNextLine())
                processLine(scanner.nextLine());
        }
    }

    protected void processLine(String aLine) {
        // Use a second Scanner to parse the content of each line
        Scanner scanner = new Scanner(aLine);
        if (scanner.hasNext()) {
            String strLine = scanner.nextLine();
            // List will tell us the total number of edges
            lstData.add(strLine);
        }
        else
            System.out.println("Error processing line in file.");
    }

    protected void parseAndAddLine() {
        Scanner scanner;
        double iNumOne = 0;
        String strCurrencyOne = "";
        double dNumTwo = 0;
        String strCurrencyTwo= "";
        int iVertexNum = 0;
        // Loop through the data list and parse each line
        for (int iLineNum = 0; iLineNum < lstData.size(); ++iLineNum) {
            scanner = new Scanner(lstData.get(iLineNum));
            scanner.useDelimiter(" ");
            // While there are still elements in the line to read
            // assign each value read in to variables to use later
            while (scanner.hasNext()) {
                iNumOne = scanner.nextInt();
                strCurrencyOne = scanner.next();
                // Account for the '=' sign
                scanner.next();
                // Continue reading
                dNumTwo = scanner.nextDouble();
                strCurrencyTwo = scanner.next();
            }
            // Map first currency read in to vertex number
            if (dictCorresp.get(strCurrencyOne) == null) {
                dictCorresp.put(strCurrencyOne, iVertexNum);
                lstReverseCorresp.add(strCurrencyOne);
                ++iVertexNum;
            }

            if (dictCorresp.get(strCurrencyTwo) == null) {
                dictCorresp.put(strCurrencyTwo, iVertexNum);
                lstReverseCorresp.add(strCurrencyTwo);
                ++iVertexNum;
            }
        }
    }

    protected void fillAdjMat() {
        // Read through again to add rates based on verts in dictionary
        Scanner scanner;
        double iNumOne = 0;
        String strCurrencyOne = "";
        double dNumTwo = 0;
        String strCurrencyTwo= "";
        // Loop through the data list and parse each line
        for (int iLineNum = 0; iLineNum < lstData.size(); ++iLineNum) {
            scanner = new Scanner(lstData.get(iLineNum));
            scanner.useDelimiter(" ");
            // While there are still elements in the line to read
            // assign each value read in to variables to use later
            while (scanner.hasNext()) {
                iNumOne = scanner.nextInt();
                strCurrencyOne = scanner.next();
                // Account for the '=' sign
                scanner.next();
                // Continue reading
                dNumTwo = scanner.nextDouble();
                strCurrencyTwo = scanner.next();
            }
            aiAdjMat[dictCorresp.get(strCurrencyOne)][dictCorresp.get(strCurrencyTwo)] = dNumTwo;
            aiAdjMat[dictCorresp.get(strCurrencyTwo)][dictCorresp.get(strCurrencyOne)] = 1 / dNumTwo;
        }
    }
}


