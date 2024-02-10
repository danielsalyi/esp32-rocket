#ifndef SEQUENCES_H
#define SEQUENCES_H


class Sequences
{
    private:
    bool arm;

    public:
    Sequences();

    void armSequence();
    void disarmSequence();

    void launchSequence();
    void abortSequence();
};

Sequences extern sequences;

#endif