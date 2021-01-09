namespace cerium {

// set all mat values at given channel to given value
// https://stackoverflow.com/questions/23510571/how-to-set-given-channel-of-a-cvmat-to-a-given-value-efficiently-without-chang
auto setChannel(Mat &mat, unsigned int channel, unsigned char value) -> void {
    // make sure have enough channels
    if (mat.channels() < channel+1)
        return;

    // check mat is continuous or not
    if (mat.isContinuous())
        mat.reshape(1, mat.rows*mat.cols).col(channel).setTo(Scalar(value));
    else{
        for (int i = 0; i < mat.rows; i++)
            mat.row(i).reshape(1, mat.cols).col(channel).setTo(Scalar(value));
    }
}

}