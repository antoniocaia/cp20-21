int maxim = INT32_MIN;

int myMax(Node *root)
{
	int sl = 0;
	int sr = 0;

	if (root->left == NULL && root->right == NULL)
		return root->data;

	if (root->left != NULL)
		sl = myMax(root->left);

	if (root->right != NULL)
		sr = myMax(root->right);


	if (root->left == NULL)
		return sr + root->data;
	else if (root->right == NULL)
		return sl + root->data;
	else
	{
	    int tmp_tot = sl + sr + root->data;

	    if (tmp_tot > maxim)
		    maxim = tmp_tot;
		
		if (sl > sr)
			return sl + root->data;
		else
			return sr + root->data;
	}
}

int maxPathSum(Node *root)
{
    maxim = INT32_MIN;
	myMax(root);
	return maxim;
}