#pragma once



//WARNING: since this will unlock/lock the python global interpreter lock,
//         it will not work recursively

//this is basically a scoped version of a Py_BEGIN_ALLOW_THREADS .. Py_END_ALLOW_THREADS block
class CPyThreadState
{
  public:
    CPyThreadState(bool save = true)
    {
      m_threadState = NULL;

      if (save)
        Save();
    }

    ~CPyThreadState()
    {
      Restore();
    }

    void Save()
    {
      if (!m_threadState)
        m_threadState = PyEval_SaveThread(); //same as Py_BEGIN_ALLOW_THREADS
    }

    void Restore()
    {
      if (m_threadState)
      {
        PyEval_RestoreThread(m_threadState); //same as Py_END_ALLOW_THREADS
        m_threadState = NULL;
      }
    }

  private:
    PyThreadState* m_threadState;
};

