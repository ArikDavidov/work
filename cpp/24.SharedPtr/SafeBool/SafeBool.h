

class Testable {
    bool ok_;
    typedef void (Testable::*bool_type)() const;
    void this_type_does_not_support_comparisons() const {}
  public:
    explicit Testable(bool b=true):ok_(b) {}

    operator bool_type() const {
      return ok_==true ? 
        &Testable::this_type_does_not_support_comparisons : 0;
    }
  };
