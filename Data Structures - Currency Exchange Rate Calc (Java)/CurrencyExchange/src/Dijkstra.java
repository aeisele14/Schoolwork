import java.util.Dictionary;
import java.util.Stack;
import java.util.Vector;

/**
 * Created by mhall on 1/20/14.
 */
public class Dijkstra {
    public static void doDijkstra(double[][] aiAdgMat, Dictionary<String, Integer> dictCorresp, Vector<String> lstReverseCorresp) {
        // Set up adjacency matrix for graph.

        // Use a list (vector, actually) to keep track of the vertices that
        // are not in the set S of vertices whose minimum weight path has
        // already been found.
        int iSize = dictCorresp.size();
        Vector<Integer> vVertsMinPathNotYet = new Vector<Integer>(iSize);
        // Initially every vertex is in this list.
        for (int iVertex = 0; iVertex < iSize; ++iVertex)
            vVertsMinPathNotYet.add(iVertex);
        // Arrays for distances and predecessors.
        double[] aDist = new double[iSize];
        int[] aPred = new int[iSize];
        for (int iVertex = 0; iVertex < iSize; ++iVertex) {
            // Initially all distances are infinite and all predecessors are a
            // nonexistent vertex.
            aDist[iVertex] = 0;
            aPred[iVertex] = -1;
        }
        // We are finding distances from vertex 0 to all of the others, so we
        // can initialize the distance for vertex 0 to be 0.
        aDist[0] = 1;

        // Now, do Dijkstra's algorithm. Keep going as long as we have vertices
        // with no minimum-weight path found yet.
        while (!vVertsMinPathNotYet.isEmpty()) {
            // Find the vertex in the list whose current distance is a max.
            // dMaxDist is the max distance found so far for vertices in the list
            // and dMaxDist tells where it is in the list.
            double dMaxDist = 0;
            int iMaxDistIndex = -1;
            for (int iIndex = 0; iIndex < vVertsMinPathNotYet.size(); ++iIndex) {
                // Get the vertex in slot iIndex of the list.
                int iVertex = vVertsMinPathNotYet.elementAt(iIndex);
                // Check whether this vertex has a larger distance than the biggest
                // distance found so far.
                if (aDist[iVertex] > dMaxDist) {
                    // Found vertex with a larger distance. Keep track of where it is
                    // in the list and update the max distance.
                    iMaxDistIndex = iIndex;
                    dMaxDist = aDist[iVertex];
                }
            }
            // We have found the vertex with the maximum distance. Remove it from the
            // list, then update distances for all vertices adjacent to it. Note that
            // dMaxDist holds the distance for this vertex, so we do not need to get
            // it again.
            int iNextVertex = vVertsMinPathNotYet.elementAt(iMaxDistIndex);
            vVertsMinPathNotYet.remove(iMaxDistIndex);
            // Get the row in the adjacency matrix that corresponds to this vertex.
            double [] aiAdjMatRow = aiAdgMat[iNextVertex];
            // Loop through the vertices adjacent to this vertex. For this we loop
            // through all vertices, but only consider those with a nonzero entry in
            // the adjacency matrix.
            for (int iAdjVertex = 0; iAdjVertex < aiAdjMatRow.length; ++iAdjVertex) {
                // Check for nonzero value (weight) in the adjacency matrix.
                double iWeight = aiAdjMatRow[iAdjVertex];
                if (iWeight != 0) {
                    // Calculate the distance to the adjacent vertex we get from going
                    // through the max-distance vertex.
                    double iDistThruMinDist = dMaxDist * iWeight;
                    // If the new distance is larger, update the distance and predecessor
                    // data for the adjacent vertex.
                    if (iDistThruMinDist > aDist[iAdjVertex]) {
                        aDist[iAdjVertex] = iDistThruMinDist;
                        aPred[iAdjVertex] = iNextVertex;
                    }
                }
            }
        }
        // Finished. Print the max distances and predecessors.
        /*System.out.println("Max distances from vertex 0:");
        for (int iVertex = 0; iVertex < iSize; ++iVertex) {
            System.out.println("\tTo vertex " + dictCorresp.get(iVertex) + ": " + aDist[iVertex]);
        }*/

        System.out.println("\nPredecessors:");
        Stack<Integer> stkPreds = new Stack<Integer>();
        double dOverallRate = 1.0;
        for (int i = 0; i < aPred.length; ++i) {
            stkPreds.push(aPred[i]);
            dOverallRate *= aDist[i];
        }
        for (int iVertex = 0; iVertex < iSize; ++iVertex) {
            System.out.println("\tPredecessor of " + lstReverseCorresp.elementAt(iVertex) + " is " + lstReverseCorresp.elementAt(stkPreds.pop()));
        }
        System.out.println("Overall exchange rate: " + dOverallRate);
    }
}
