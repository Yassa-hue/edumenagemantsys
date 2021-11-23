
USER : id | name | email | password | is_doctor
        ^
        --------------------------------------
                               |             |
USER_COURSE_REL : course_id | user_id        |
                     |                       |
          ------------                       |
          v                                  |
COURSE : id | code                           |
          ^                                  |
          ------------------------           |
                                 |           |
ASSIGNMENT : id | statement | course_id      |
              ^                              |
              |              -----------------
              |              |
ANSWER : assignment_id | user_id | grade
